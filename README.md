# p43lz3r_Waveshare_ESP32S3_Touch_LCD_7_LVGL_CANbus
Example showing simple LVGL UI and CAN interface usage on Waveshare_ESP32S3_Touch_LCD_7 display

- Use VScode and Platformio to compile

If the GUI is designed in Squareline Studio, the interesting files are
- ui_events.h - contains the function declarations
- ui_events.cpp - contains the function definitions, for example what shall happen if you press a button in the GUI.

How to get the the display up n running:
- This folder of the original ESP32 DISPLAY PANEL library is a good start, so download and open it in Platformio:

https://github.com/esp-arduino-libs/ESP32_Display_Panel/tree/master/examples/platformio/lvgl_v8_port

- The esp_panel_board_custom_conf.h from the [demo library](https://files.waveshare.com/wiki/ESP32-S3-Touch-LCD-7/ESP32-S3-Touch-LCD-7-Demo.zip) contains all necessary adjustments for the 7 inch display to work

to be continued ...
