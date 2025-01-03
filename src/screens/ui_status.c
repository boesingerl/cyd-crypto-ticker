// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: cryptowatch

#include "../ui.h"

void ui_status_screen_init(void)
{
    ui_status = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_status, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(ui_status, LV_OBJ_FLAG_CLICKABLE);

    LV_IMAGE_DECLARE(bg_candle);
    lv_obj_t * img1 = lv_image_create(ui_status);
    lv_image_set_src(img1, &bg_candle);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

    ui_day1 = lv_label_create(ui_status);
    lv_obj_set_width(ui_day1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_day1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_day1, 9);
    lv_obj_set_y(ui_day1, 6);
    lv_label_set_text(ui_day1, "12/22");
    lv_obj_set_style_text_color(ui_day1, lv_color_hex(0xD1C8C8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_day1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_day1, &ui_font_NerdFont18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_time1 = lv_label_create(ui_status);
    lv_obj_set_width(ui_time1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_time1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_time1, 79);
    lv_obj_set_y(ui_time1, 4);
    lv_label_set_text(ui_time1, "00:00");
    lv_obj_set_style_text_font(ui_time1, &ui_font_NerdFont22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_crypto1 = lv_label_create(ui_status);
    lv_obj_set_width(ui_crypto1, 50);   /// 1
    lv_obj_set_height(ui_crypto1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_style_text_align(ui_crypto1 , LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_x(ui_crypto1, -5);
    lv_obj_set_y(ui_crypto1, 12);
    lv_obj_set_align(ui_crypto1, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_crypto1, crypto);
    lv_obj_set_style_text_color(ui_crypto1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_crypto1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_crypto1, &ui_font_NerdFont18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cryptovalue = lv_label_create(ui_status);
    lv_obj_set_width(ui_cryptovalue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cryptovalue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_cryptovalue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_cryptovalue, "00000.0");
    lv_obj_set_style_text_color(ui_cryptovalue, lv_color_hex(0x7EF70C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cryptovalue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cryptovalue, &ui_font_NerdFont50, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cryptohigh = lv_label_create(ui_status);
    lv_obj_set_width(ui_cryptohigh, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cryptohigh, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_cryptohigh, -38);
    lv_obj_set_y(ui_cryptohigh, 186);
    lv_obj_set_align(ui_cryptohigh, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_cryptohigh, "00000.0");
    lv_obj_set_style_text_color(ui_cryptohigh, lv_color_hex(0xFF0404), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cryptohigh, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cryptohigh, &ui_font_NerdFont18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cryptolow = lv_label_create(ui_status);
    lv_obj_set_width(ui_cryptolow, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cryptolow, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_cryptolow, -199);
    lv_obj_set_y(ui_cryptolow, 188);
    lv_obj_set_align(ui_cryptolow, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_cryptolow, "00000.0");
    lv_obj_set_style_text_color(ui_cryptolow, lv_color_hex(0x0BBB60), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cryptolow, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cryptolow, &ui_font_NerdFont18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cog3 = lv_label_create(ui_status);
    lv_obj_set_width(ui_cog3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_cog3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_cog3, 203);
    lv_obj_set_y(ui_cog3, 5);
    lv_label_set_text(ui_cog3, "x");
    lv_obj_set_style_text_color(ui_cog3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_cog3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cog3, &ui_font_FA38, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_cog3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_bg_opa(ui_cog3, LV_OPA_TRANSP, 0);

    lv_obj_add_event_cb(ui_cog3, ui_event_to_settings, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_status, ui_event_to_weather, LV_EVENT_ALL, NULL);

}
