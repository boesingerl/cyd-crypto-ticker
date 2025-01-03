#include "ui.h"
#include "ui_helpers.h"
#include <Preferences.h>

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_graph
void ui_graph_screen_init(void);
lv_obj_t * ui_graph;
lv_obj_t * ui_background;
lv_obj_t * ui_day;
lv_obj_t * ui_time;
lv_obj_t * ui_crypto;
lv_obj_t * ui_Chart1;
void ui_event_to_settings(lv_event_t * e);
void ui_event_to_status(lv_event_t * e);
lv_obj_t * ui_cog;
// CUSTOM VARIABLES


// SCREEN: ui_currtime
void ui_currtime_screen_init(void);
void ui_event_to_graph(lv_event_t * e);
lv_obj_t * ui_currtime;
lv_obj_t * ui_day2;
lv_obj_t * ui_time2;
// CUSTOM VARIABLES


// SCREEN: ui_weather
void ui_weather_screen_init(void);
lv_obj_t * ui_weather;
lv_obj_t * ui_background2;
lv_obj_t * ui_day3;
lv_obj_t * ui_time3;
lv_obj_t * ui_weather_icon;
lv_obj_t * ui_temperature;
lv_obj_t * ui_weatherindicator;
lv_obj_t * ui_location;
void ui_event_to_currtime(lv_event_t * e);
lv_obj_t * ui_cog1;
// CUSTOM VARIABLES


// SCREEN: ui_status
void ui_status_screen_init(void);
lv_obj_t * ui_status;
lv_obj_t * ui_background1;
lv_obj_t * ui_day1;
lv_obj_t * ui_time1;
lv_obj_t * ui_crypto1;
lv_obj_t * ui_cryptovalue;
lv_obj_t * ui_cryptohigh;
lv_obj_t * ui_cryptolow;
void ui_event_to_weather(lv_event_t * e);
lv_obj_t * ui_cog3;

// SCREEN: ui_settings
void ui_settings_screen_init(void);
lv_obj_t * ui_settings;
lv_obj_t * kb;
lv_obj_t * kb_cont;
lv_obj_t * ssid_ta;
lv_obj_t * password_ta;
lv_obj_t * lat_ta;
lv_obj_t * long_ta;
lv_obj_t * crypto_ta;
lv_obj_t * timespan_ta;
lv_obj_t * loc_ta;


char* ssid;
char* password;
char* latitude;
char* longitude;
char* crypto;
char* timespan;
char* location;

void load_preferences() {
    Preferences preferences;
    preferences.begin("usr", false); 

    // Load and set values for each text area
    String ssid_str = preferences.getString("ssid", SSID);
    ssid = strdup(ssid_str.c_str());

    String password_str = preferences.getString("password", PASSWORD);
    password = strdup(password_str.c_str());

    String latitude_str = preferences.getString("latitude", LATITUDE);
    latitude = strdup(latitude_str.c_str());

    String longitude_str = preferences.getString("longitude", LONGITUDE);
    longitude = strdup(longitude_str.c_str());

    String crypto_str = preferences.getString("crypto", CRYPTO);
    crypto = strdup(crypto_str.c_str());

    String timespan_str = preferences.getString("timespan", TIMESPAN);
    timespan = strdup(timespan_str.c_str());

    String location_str = preferences.getString("location", LOCATION);
    location = strdup(location_str.c_str());

    preferences.end(); // Close preferences
}
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_to_settings(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_settings, LV_SCR_LOAD_ANIM_FADE_IN, 10, 0, &ui_settings_screen_init);
    }
}

void ui_event_to_status(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = (lv_obj_t *)lv_event_get_target(e);

    if(event_code == LV_EVENT_CLICKED) {
        if(target == ui_cog){
            return;
        }
        _ui_screen_change(&ui_status, LV_SCR_LOAD_ANIM_FADE_IN, 10, 0, &ui_status_screen_init);
    }
}

void ui_event_to_graph(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = (lv_obj_t *)lv_event_get_target(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_graph, LV_SCR_LOAD_ANIM_FADE_IN, 10, 0, &ui_graph_screen_init);
    }
}

void ui_event_to_currtime(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = (lv_obj_t *)lv_event_get_target(e);

    if(event_code == LV_EVENT_CLICKED) {
        if(target == ui_cog1){
            return;
        }
        _ui_screen_change(&ui_currtime, LV_SCR_LOAD_ANIM_FADE_IN, 10, 0, &ui_currtime_screen_init);
    }
}

void ui_event_to_weather(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = (lv_obj_t *)lv_event_get_target(e);

    if(event_code == LV_EVENT_CLICKED) {
        if(target == ui_cog3){
            return;
        }
        _ui_screen_change(&ui_weather, LV_SCR_LOAD_ANIM_FADE_IN, 10, 0, &ui_weather_screen_init);
    }
}
