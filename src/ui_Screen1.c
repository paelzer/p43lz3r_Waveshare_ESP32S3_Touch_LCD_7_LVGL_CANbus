// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.1
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x7C71DA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_startScreen = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_startScreen, 744);
    lv_obj_set_height(ui_startScreen, 425);
    lv_obj_set_align(ui_startScreen, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_startScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_headingLbl = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_headingLbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_headingLbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_headingLbl, 0);
    lv_obj_set_y(ui_headingLbl, -187);
    lv_obj_set_align(ui_headingLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_headingLbl, "*** Vehicle data interface ***");
    lv_obj_set_style_text_color(ui_headingLbl, lv_color_hex(0x0B4ECF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_headingLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_headingLbl, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_oilTempLbl = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_oilTempLbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_oilTempLbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_oilTempLbl, -280);
    lv_obj_set_y(ui_oilTempLbl, -100);
    lv_obj_set_align(ui_oilTempLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_oilTempLbl, "Oil temperature:");
    lv_obj_set_style_text_color(ui_oilTempLbl, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_oilTempLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_oilTempLbl, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_oilTempLbl, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_oilTempValueLbl = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_oilTempValueLbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_oilTempValueLbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_oilTempValueLbl, -170);
    lv_obj_set_y(ui_oilTempValueLbl, -100);
    lv_obj_set_align(ui_oilTempValueLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_oilTempValueLbl, "0");
    lv_obj_set_style_text_font(ui_oilTempValueLbl, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_oilTempUnitLbl = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_oilTempUnitLbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_oilTempUnitLbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_oilTempUnitLbl, -120);
    lv_obj_set_y(ui_oilTempUnitLbl, -100);
    lv_obj_set_align(ui_oilTempUnitLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_oilTempUnitLbl, "°C");
    lv_obj_set_style_text_color(ui_oilTempUnitLbl, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_oilTempUnitLbl, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_oilTempUnitLbl, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rawCanMsgOilLbl = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_rawCanMsgOilLbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_rawCanMsgOilLbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_rawCanMsgOilLbl, -280);
    lv_obj_set_y(ui_rawCanMsgOilLbl, -57);
    lv_obj_set_align(ui_rawCanMsgOilLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rawCanMsgOilLbl, "Raw message:");
    lv_obj_set_style_text_align(ui_rawCanMsgOilLbl, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rawCanMsgOilLbl, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rawMsgValueOilLbl = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_rawMsgValueOilLbl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_rawMsgValueOilLbl, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_rawMsgValueOilLbl, -170);
    lv_obj_set_y(ui_rawMsgValueOilLbl, -57);
    lv_obj_set_align(ui_rawMsgValueOilLbl, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rawMsgValueOilLbl, "0");
    lv_obj_set_style_text_font(ui_rawMsgValueOilLbl, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_updateOilTempBtn = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_updateOilTempBtn, 50);
    lv_obj_set_height(ui_updateOilTempBtn, 50);
    lv_obj_set_x(ui_updateOilTempBtn, 365);
    lv_obj_set_y(ui_updateOilTempBtn, 198);
    lv_obj_set_align(ui_updateOilTempBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_updateOilTempBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_updateOilTempBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_updateOilTempBtn, lv_color_hex(0x0410E2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_updateOilTempBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_updateOilTempBtn, lv_color_hex(0x383535), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_updateOilTempBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_updateOilTempBtn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_updateOilTempBtn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_canMsgSendBtn = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_canMsgSendBtn, 50);
    lv_obj_set_height(ui_canMsgSendBtn, 50);
    lv_obj_set_x(ui_canMsgSendBtn, 285);
    lv_obj_set_y(ui_canMsgSendBtn, 198);
    lv_obj_set_align(ui_canMsgSendBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_canMsgSendBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_canMsgSendBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_canMsgSendBtn, lv_color_hex(0xE20404), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_canMsgSendBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_canMsgSendBtn, lv_color_hex(0x383535), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_canMsgSendBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_canMsgSendBtn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_canMsgSendBtn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_myCustomBtn = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_myCustomBtn, 50);
    lv_obj_set_height(ui_myCustomBtn, 50);
    lv_obj_set_x(ui_myCustomBtn, 205);
    lv_obj_set_y(ui_myCustomBtn, 199);
    lv_obj_set_align(ui_myCustomBtn, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_myCustomBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_myCustomBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_myCustomBtn, lv_color_hex(0xE9F111), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_myCustomBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_myCustomBtn, lv_color_hex(0x383535), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_myCustomBtn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_myCustomBtn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_myCustomBtn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_updateOilTempBtn, ui_event_updateOilTempBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_canMsgSendBtn, ui_event_canMsgSendBtn, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_myCustomBtn, ui_event_myCustomBtn, LV_EVENT_ALL, NULL);
    uic_startScreen = ui_startScreen;
    uic_headingLbl = ui_headingLbl;
    uic_oilTempLbl = ui_oilTempLbl;
    uic_oilTempValueLbl = ui_oilTempValueLbl;
    uic_oilTempUnitLbl = ui_oilTempUnitLbl;
    uic_rawCanMsgOilLbl = ui_rawCanMsgOilLbl;
    uic_rawMsgValueOilLbl = ui_rawMsgValueOilLbl;
    uic_updateOilTempBtn = ui_updateOilTempBtn;
    uic_canMsgSendBtn = ui_canMsgSendBtn;
    uic_myCustomBtn = ui_myCustomBtn;

}
