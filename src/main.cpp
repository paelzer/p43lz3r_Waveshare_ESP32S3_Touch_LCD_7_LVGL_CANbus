// main.ino
#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include "lvgl_v8_port.h"
#include "ui.h"
#include <WaveshareCAN.h>

using namespace esp_panel::drivers;
using namespace esp_panel::board;

WaveshareCAN can;

// Declare the function that will be called from C code
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif


void setup() {
  Serial.begin(115200);

  // Initialize the TWAI hardware
  //can.initIOExpander();
  can.begin(CAN_250KBPS);

  Serial.println("Initializing board");
  Board *board = new Board();
  board->init();

#if LVGL_PORT_AVOID_TEARING_MODE
  auto lcd = board->getLCD();
  lcd->configFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
#if ESP_PANEL_DRIVERS_BUS_ENABLE_RGB && CONFIG_IDF_TARGET_ESP32S3
  auto lcd_bus = lcd->getBus();
  if (lcd_bus->getBasicAttributes().type == ESP_PANEL_BUS_TYPE_RGB) {
    static_cast<BusRGB *>(lcd_bus)->configRGB_BounceBufferSize(lcd->getFrameWidth() * 10);
  }
#endif
#endif

  // Add a small delay for peripherals to stabilize - important for reliability!
  delay(100);

  // Check for initialization success - important for reliability!
  if (!board->begin()) {
    Serial.println("Board initialization failed! Check connections and restart.");
    while (1) { delay(1000); }  // Halt with error indication
  }

  Serial.println("Initializing LVGL");
  lvgl_port_init(board->getLCD(), board->getTouch());

  Serial.println("Creating UI");
  /* Lock the mutex due to the LVGL APIs are not thread-safe */
  lvgl_port_lock(-1);
  ui_init();
  lvgl_port_unlock();
}

void loop() {
  // You don't need any special code in the loop to handle button clicks
  // The LVGL task handler (in lvgl_port_task) processes touch events
  // and calls the registered callbacks automatically

  // Your regular loop code goes here
  delay(10);  // Keep this short delay from your original working code
}