// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: cryptowatch

#include <Preferences.h>
#include "../ui.h"

#if LV_USE_KEYBOARD


static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_target(e);
    lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_remove_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(kb_cont, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(kb_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

void load_ta_values() {

    // load preferences
    load_preferences();

    // Load and set values for each text area
    lv_textarea_set_text(ssid_ta, ssid);
    lv_textarea_set_text(password_ta, password);
    lv_textarea_set_text(lat_ta, latitude);
    lv_textarea_set_text(long_ta, longitude);
    lv_textarea_set_text(crypto_ta, crypto);
    lv_textarea_set_text(timespan_ta, timespan);
    lv_textarea_set_text(loc_ta, location);
}

void save_textarea_values() {
    Preferences preferences;
    preferences.begin("usr", false); // Open preferences in read-write mode

    // Save values from each text area
    preferences.putString("ssid", lv_textarea_get_text(ssid_ta));
    preferences.putString("password", lv_textarea_get_text(password_ta));
    preferences.putString("latitude", lv_textarea_get_text(lat_ta));
    preferences.putString("longitude", lv_textarea_get_text(long_ta));
    preferences.putString("crypto", lv_textarea_get_text(crypto_ta));
    preferences.putString("timespan", lv_textarea_get_text(timespan_ta));
    preferences.putString("location", lv_textarea_get_text(loc_ta));

    preferences.end(); // Close preferences
}

void ui_event_back(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = (lv_obj_t *)lv_event_get_target(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_graph, LV_SCR_LOAD_ANIM_FADE_IN, 10, 0, &ui_graph_screen_init);
    }
}

void ui_event_apply(lv_event_t * e)
{
    save_textarea_values();
    ESP.restart();
}

void ui_settings_screen_init(void)
{
    ui_settings = lv_obj_create(NULL);
    lv_obj_set_size(ui_settings, LV_HOR_RES, LV_VER_RES * 3); // Set size to 240x320
    lv_obj_add_flag(ui_settings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    /*Create a 'Back' button on the top left*/
    lv_obj_t * btn_back = lv_btn_create(ui_settings);
    lv_obj_align(btn_back, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_bg_color(btn_back, lv_color_hex(0xAA0000), LV_PART_MAIN | LV_STATE_DEFAULT); // Set background color to red
    lv_obj_t * label_back = lv_label_create(btn_back);
    lv_label_set_text(label_back, "Back");
    lv_obj_add_event_cb(btn_back, ui_event_back, LV_EVENT_CLICKED, NULL);

    /*Create an 'Apply' button on the top right*/
    lv_obj_t * btn_apply = lv_btn_create(ui_settings);
    lv_obj_align(btn_apply, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_set_style_bg_color(btn_apply, lv_color_hex(0x00AA00), LV_PART_MAIN | LV_STATE_DEFAULT); // Set background color to green
    lv_obj_t * label_apply = lv_label_create(btn_apply);
    lv_label_set_text(label_apply, "Apply");
    lv_obj_add_event_cb(btn_apply, ui_event_apply, LV_EVENT_CLICKED, NULL);

    // Calculate the center position for the text areas
    int screen_width = lv_obj_get_width(ui_settings);
    int ta_width = 140;
    int label_width = 120; // Assuming a fixed width for labels
    int total_width = label_width + ta_width;
    int x_center = (screen_width - total_width) / 2;

    /*Create text areas with labels*/
    lv_obj_t * label1 = lv_label_create(ui_settings);
    lv_label_set_text(label1, "SSID");
    lv_obj_align(label1, LV_ALIGN_TOP_LEFT, x_center, 60);

    ssid_ta = lv_textarea_create(ui_settings);
    lv_obj_align(ssid_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 50);
    lv_textarea_set_placeholder_text(ssid_ta, "SSID");
    lv_obj_set_size(ssid_ta, ta_width, 40);

    lv_obj_t * label2 = lv_label_create(ui_settings);
    lv_label_set_text(label2, "Password");
    lv_obj_align(label2, LV_ALIGN_TOP_LEFT, x_center, 110);

    password_ta = lv_textarea_create(ui_settings);
    lv_obj_align(password_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 100);
    lv_textarea_set_placeholder_text(password_ta, "Password");
    lv_obj_set_size(password_ta, ta_width, 40);

    lv_obj_t * label3 = lv_label_create(ui_settings);
    lv_label_set_text(label3, "Lattitude");
    lv_obj_align(label3, LV_ALIGN_TOP_LEFT, x_center, 160);

    lat_ta = lv_textarea_create(ui_settings);
    lv_obj_align(lat_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 150);
    lv_obj_set_size(lat_ta, ta_width, 40);
    lv_textarea_set_placeholder_text(lat_ta, "***REMOVED***");

    lv_obj_t * label4 = lv_label_create(ui_settings);
    lv_label_set_text(label4, "Longitude");
    lv_obj_align(label4, LV_ALIGN_TOP_LEFT, x_center, 210);

    long_ta = lv_textarea_create(ui_settings);
    lv_obj_align(long_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 200);
    lv_obj_set_size(long_ta, ta_width, 40);
    lv_textarea_set_placeholder_text(long_ta, "***REMOVED***");

    lv_obj_t * label5 = lv_label_create(ui_settings);
    lv_label_set_text(label5, "Crypto Token");
    lv_obj_align(label5, LV_ALIGN_TOP_LEFT, x_center, 260);

    crypto_ta = lv_textarea_create(ui_settings);
    lv_obj_align(crypto_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 250);
    lv_obj_set_size(crypto_ta, ta_width, 40);
    lv_textarea_set_placeholder_text(crypto_ta, "BTC");

    lv_obj_t * label6 = lv_label_create(ui_settings);
    lv_label_set_text(label6, "Time Format");
    lv_obj_align(label6, LV_ALIGN_TOP_LEFT, x_center, 310);

    timespan_ta = lv_textarea_create(ui_settings);
    lv_obj_align(timespan_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 300);
    lv_obj_set_size(timespan_ta, ta_width, 40);
    lv_textarea_set_placeholder_text(timespan_ta, "12h");

    lv_obj_t * label7 = lv_label_create(ui_settings);
    lv_label_set_text(label7, "Place Name");
    lv_obj_align(label7, LV_ALIGN_TOP_LEFT, x_center, 360);

    loc_ta = lv_textarea_create(ui_settings);
    lv_obj_align(loc_ta, LV_ALIGN_TOP_LEFT, x_center + label_width, 350);
    lv_textarea_set_placeholder_text(loc_ta, "Loc");
    lv_obj_set_size(loc_ta, ta_width, 40);

    /*Create a keyboard to use it with any of the text areas*/
    kb_cont = lv_obj_create(ui_settings);
    lv_obj_set_size(kb_cont, LV_HOR_RES, LV_VER_RES / 2);
    lv_obj_add_flag(kb_cont, LV_OBJ_FLAG_FLOATING);
    lv_obj_add_flag(kb_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align(kb_cont, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_t *kb = lv_keyboard_create(kb_cont);
    lv_obj_set_size(kb, LV_HOR_RES - 20, (LV_VER_RES / 2) - 30);

    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(ssid_ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(password_ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(lat_ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(long_ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(crypto_ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(timespan_ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_add_event_cb(loc_ta, ta_event_cb, LV_EVENT_ALL, kb);

    load_ta_values();
}



// Call the function to load values into text areas

#endif


