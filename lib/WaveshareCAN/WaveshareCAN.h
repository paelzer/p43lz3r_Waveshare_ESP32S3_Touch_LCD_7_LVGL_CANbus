/*
  WaveshareCAN.h - Library for ESP32 TWAI (CAN bus) communication with Waveshare boards
  Created by Claude, April 30, 2025
*/

#ifndef WAVESHARE_CAN_H
#define WAVESHARE_CAN_H

#include <Arduino.h>
#include "driver/twai.h"
#include <esp_io_expander.hpp>

// Default pins used to connect to CAN bus transceiver
#define CAN_DEFAULT_RX_PIN 19
#define CAN_DEFAULT_TX_PIN 20

// I2C Expander defaults
#define CAN_EXPANDER_I2C_ADDR (ESP_IO_EXPANDER_I2C_CH422G_ADDRESS)
#define CAN_EXPANDER_I2C_SDA_PIN 8
#define CAN_EXPANDER_I2C_SCL_PIN 9

// IO Expander pin definitions
#define CAN_TP_RST 1
#define CAN_LCD_BL 2
#define CAN_LCD_RST 3
#define CAN_SD_CS 4
#define CAN_USB_SEL 5

// CAN bus speed definitions
#define CAN_5KBPS    TWAI_TIMING_CONFIG_5KBITS()
#define CAN_10KBPS   TWAI_TIMING_CONFIG_10KBITS()
#define CAN_20KBPS   TWAI_TIMING_CONFIG_20KBITS()
#define CAN_50KBPS   TWAI_TIMING_CONFIG_50KBITS()
#define CAN_100KBPS  TWAI_TIMING_CONFIG_100KBITS()
#define CAN_125KBPS  TWAI_TIMING_CONFIG_125KBITS()
#define CAN_250KBPS  TWAI_TIMING_CONFIG_250KBITS()
#define CAN_500KBPS  TWAI_TIMING_CONFIG_500KBITS()
#define CAN_800KBPS  TWAI_TIMING_CONFIG_800KBITS()
#define CAN_1000KBPS TWAI_TIMING_CONFIG_1MBITS()

// Forward declaration
namespace esp_expander {
    class CH422G;
}

class WaveshareCAN {
public:
    // Constructor with optional pin configuration
    WaveshareCAN(int rxPin = CAN_DEFAULT_RX_PIN, int txPin = CAN_DEFAULT_TX_PIN);

    // Destructor
    ~WaveshareCAN();

    // Initialize IO expander
    bool initIOExpander(int sclPin = CAN_EXPANDER_I2C_SCL_PIN,
                        int sdaPin = CAN_EXPANDER_I2C_SDA_PIN,
                        int addr = CAN_EXPANDER_I2C_ADDR);

    // Begin CAN communication with specified speed
    bool begin(twai_timing_config_t speedConfig = CAN_500KBPS);

    // End CAN communication
    void end();

    // Check if packet is available to read
    int available();

    // Send a CAN packet/message
    bool sendMessage(uint32_t id, bool extended, uint8_t* data, uint8_t length, bool rtr = false);

    // Simple overload for common use case (standard frame)
    bool sendMessage(uint32_t id, uint8_t* data, uint8_t length);

    // Receive a CAN packet/message (returns number of bytes read or -1 for error)
    int receiveMessage(uint32_t* id, bool* extended, uint8_t* data, uint8_t* length, bool* rtr = nullptr);

    // Filter messages by ID (0 = accept all)
    void filter(uint32_t id, uint32_t mask = 0);

    // Get status information
    bool getStatus(twai_status_info_t* status);

    // Set to listen-only mode (true) or normal mode (false)
    bool setListenOnly(bool listenOnly);

    // Process alerts (returns true if any alerts were triggered)
    bool processAlerts(uint32_t* alertsTriggered = nullptr);

    // Set alert callback function
    void onAlert(void (*callback)(uint32_t));

private:
    int _rxPin;
    int _txPin;
    bool _initialized;
    bool _expanderInitialized;
    bool _listenOnly;
    esp_expander::CH422G* _expander;
    void (*_alertCallback)(uint32_t);

    // Handle CAN bus alerts
    void handleAlerts(uint32_t alerts);
};

#endif // WAVESHARE_CAN_H
