/*
  WaveshareCAN.cpp - Library for ESP32 TWAI (CAN bus) communication with Waveshare boards
  Created by Claude, April 30, 2025
*/

#include "WaveshareCAN.h"

// Constructor
WaveshareCAN::WaveshareCAN(int rxPin, int txPin) :
    _rxPin(rxPin),
    _txPin(txPin),
    _initialized(false),
    _expanderInitialized(false),
    _listenOnly(false),
    _expander(nullptr),
    _alertCallback(nullptr) {
}

// Destructor
WaveshareCAN::~WaveshareCAN() {
    end();
    if (_expander != nullptr) {
        delete _expander;
        _expander = nullptr;
    }
}

// Initialize IO expander
bool WaveshareCAN::initIOExpander(int sclPin, int sdaPin, int addr) {
    if (_expanderInitialized) {
        return true; // Already initialized
    }

    // Initialize IO expander
    _expander = new esp_expander::CH422G(sclPin, sdaPin, addr);
    if (_expander == nullptr) {
        Serial.println("Failed to create IO expander instance");
        return false;
    }

    if (!_expander->init() || !_expander->begin()) {
        Serial.println("Failed to initialize IO expander");
        delete _expander;
        _expander = nullptr;
        return false;
    }

    // Configure the IO expander pins
    _expander->enableAllIO_Output();
    _expander->multiDigitalWrite(CAN_TP_RST | CAN_LCD_RST | CAN_USB_SEL, HIGH);
    _expander->digitalWrite(CAN_LCD_BL, LOW);

    _expanderInitialized = true;
    return true;
}

// Begin CAN communication
bool WaveshareCAN::begin(twai_timing_config_t speedConfig) {
    if (_initialized) {
        return true; // Already initialized
    }

    // Configure TWAI driver
    twai_general_config_t g_config;
    if (_listenOnly) {
        g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)_txPin, (gpio_num_t)_rxPin, TWAI_MODE_LISTEN_ONLY);
    } else {
        g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)_txPin, (gpio_num_t)_rxPin, TWAI_MODE_NORMAL);
    }
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL(); // Default: accept all

    // Install TWAI driver
    if (twai_driver_install(&g_config, &speedConfig, &f_config) != ESP_OK) {
        Serial.println("Failed to install TWAI driver");
        return false;
    }

    // Start TWAI driver
    if (twai_start() != ESP_OK) {
        Serial.println("Failed to start TWAI driver");
        twai_driver_uninstall();
        return false;
    }

    // Configure alerts for both TX and RX functionality
    uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_TX_IDLE |
                               TWAI_ALERT_TX_SUCCESS | TWAI_ALERT_TX_FAILED |
                               TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR |
                               TWAI_ALERT_RX_QUEUE_FULL;

    if (twai_reconfigure_alerts(alerts_to_enable, NULL) != ESP_OK) {
        Serial.println("Failed to reconfigure alerts");
        twai_stop();
        twai_driver_uninstall();
        return false;
    }

    _initialized = true;
    return true;
}

// End CAN communication
void WaveshareCAN::end() {
    if (_initialized) {
        twai_stop();
        twai_driver_uninstall();
        _initialized = false;
    }
}

// Check if packet is available to read
int WaveshareCAN::available() {
    if (!_initialized) {
        return 0;
    }

    twai_status_info_t status;
    if (twai_get_status_info(&status) != ESP_OK) {
        return 0;
    }

    return status.msgs_to_rx;
}

// Send a CAN message (with all parameters)
bool WaveshareCAN::sendMessage(uint32_t id, bool extended, uint8_t* data, uint8_t length, bool rtr) {
    if (!_initialized || _listenOnly) {
        return false;
    }

    // Validate length
    if (length > 8) {
        length = 8; // CAN only supports up to 8 bytes
    }

    // Configure message to transmit
    twai_message_t message;
    message.identifier = id;
    message.data_length_code = length;
    message.extd = extended;
    message.rtr = rtr;

    // Copy data (if not RTR)
    if (!rtr && data != nullptr) {
        for (int i = 0; i < length; i++) {
            message.data[i] = data[i];
        }
    }

    // Queue message for transmission
    if (twai_transmit(&message, pdMS_TO_TICKS(50)) == ESP_OK) {
        return true;
    }

    return false;
}

// Simple overload for common use case (standard frame)
bool WaveshareCAN::sendMessage(uint32_t id, uint8_t* data, uint8_t length) {
    return sendMessage(id, false, data, length, false);
}

// Receive a CAN message
int WaveshareCAN::receiveMessage(uint32_t* id, bool* extended, uint8_t* data, uint8_t* length, bool* rtr) {
    if (!_initialized) {
        return -1;
    }

    twai_message_t message;
    esp_err_t result = twai_receive(&message, 0); // Non-blocking

    if (result != ESP_OK) {
        return -1; // No message available or error
    }

    // Copy message data to output parameters
    if (id != nullptr) {
        *id = message.identifier;
    }

    if (extended != nullptr) {
        *extended = message.extd;
    }

    if (length != nullptr) {
        *length = message.data_length_code;
    }

    if (rtr != nullptr) {
        *rtr = message.rtr;
    }

    // Copy data if not RTR
    if (!message.rtr && data != nullptr) {
        for (int i = 0; i < message.data_length_code; i++) {
            data[i] = message.data[i];
        }
    }

    return message.data_length_code;
}

// Filter messages by ID and mask
void WaveshareCAN::filter(uint32_t id, uint32_t mask) {
    if (!_initialized) {
        return;
    }

    // Stop driver to reconfigure
    twai_stop();

    // Uninstall driver
    twai_driver_uninstall();

    // General config (preserve current mode)
    twai_general_config_t g_config;
    if (_listenOnly) {
        g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)_txPin, (gpio_num_t)_rxPin, TWAI_MODE_LISTEN_ONLY);
    } else {
        g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)_txPin, (gpio_num_t)_rxPin, TWAI_MODE_NORMAL);
    }

    // Timing config (use 500Kbps as default)
    twai_timing_config_t t_config = CAN_500KBPS;

    // Filter config (custom)
    twai_filter_config_t f_config;
    if (mask == 0) {
        // Accept all
        f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    } else {
        // Custom filter
        f_config.acceptance_code = id;
        f_config.acceptance_mask = mask;
        f_config.single_filter = true;
    }

    // Reinstall driver with new filter
    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK) {
        Serial.println("Failed to reinstall driver with filter");
        _initialized = false;
        return;
    }

    // Restart driver
    if (twai_start() != ESP_OK) {
        Serial.println("Failed to restart driver");
        twai_driver_uninstall();
        _initialized = false;
        return;
    }

    // Reconfigure alerts
    uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_TX_IDLE |
                               TWAI_ALERT_TX_SUCCESS | TWAI_ALERT_TX_FAILED |
                               TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR |
                               TWAI_ALERT_RX_QUEUE_FULL;

    if (twai_reconfigure_alerts(alerts_to_enable, NULL) != ESP_OK) {
        Serial.println("Failed to reconfigure alerts");
        twai_stop();
        twai_driver_uninstall();
        _initialized = false;
    }
}

// Get status information
bool WaveshareCAN::getStatus(twai_status_info_t* status) {
    if (!_initialized || status == nullptr) {
        return false;
    }

    return (twai_get_status_info(status) == ESP_OK);
}

// Set listen-only mode
bool WaveshareCAN::setListenOnly(bool listenOnly) {
    if (_initialized && _listenOnly != listenOnly) {
        // Need to reinstall driver to change mode
        _listenOnly = listenOnly;
        end();
        return begin();
    }

    _listenOnly = listenOnly;
    return true;
}

// Process alerts
bool WaveshareCAN::processAlerts(uint32_t* alertsTriggered) {
    if (!_initialized) {
        return false;
    }

    uint32_t alerts;
    if (twai_read_alerts(&alerts, pdMS_TO_TICKS(0)) != ESP_OK) {
        return false;
    }

    if (alerts == 0) {
        return false; // No alerts triggered
    }

    // Save alerts to output parameter if provided
    if (alertsTriggered != nullptr) {
        *alertsTriggered = alerts;
    }

    // Handle alerts internally
    handleAlerts(alerts);

    // Call alert callback if set
    if (_alertCallback != nullptr) {
        _alertCallback(alerts);
    }

    return true;
}

// Set alert callback function
void WaveshareCAN::onAlert(void (*callback)(uint32_t)) {
    _alertCallback = callback;
}

// Handle CAN bus alerts internally
void WaveshareCAN::handleAlerts(uint32_t alerts) {
    twai_status_info_t status;
    twai_get_status_info(&status);

    // Print alert information to Serial (if needed)
    if (alerts & TWAI_ALERT_ERR_PASS) {
        Serial.println("Alert: TWAI controller has become error passive");
    }

    if (alerts & TWAI_ALERT_BUS_ERROR) {
        Serial.println("Alert: Bus error occurred");
        Serial.printf("Bus error count: %d\n", status.bus_error_count);
    }

    if (alerts & TWAI_ALERT_RX_QUEUE_FULL) {
        Serial.println("Alert: RX queue full, message lost");
        Serial.printf("RX buffered: %d, missed: %d, overrun: %d\n",
                      status.msgs_to_rx, status.rx_missed_count, status.rx_overrun_count);
    }

    if (alerts & TWAI_ALERT_TX_FAILED) {
        Serial.println("Alert: TX failed");
        Serial.printf("TX buffered: %d, errors: %d, failed: %d\n",
                      status.msgs_to_tx, status.tx_error_counter, status.tx_failed_count);
    }

    if (alerts & TWAI_ALERT_TX_SUCCESS) {
        // This is common and usually doesn't need to be printed
        // Serial.println("Alert: TX successful");
    }
}
