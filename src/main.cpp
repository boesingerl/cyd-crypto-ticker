#include <lvgl.h>
#include <TFT_eSPI.h>
#include <CST820.h>
#include <WiFi.h>

#include "Config.h"
#include "WeatherHelper.h"
#include "BinanceWebSocket.h"
#include "ui.h"
#include "TimeHelper.h"
#include "BianceCandleStick.h"

static const uint16_t screenWidth = SCREEN_WIDTH;
static const uint16_t screenHeight = SCREEN_HEIGHT;

static unsigned long lastTimeUpdate = 0;
static unsigned long lastTimeBinanceUpdate = 0;
bool startup = true;


static lv_color_t *buf1;
static lv_color_t *buf2;

TFT_eSPI tft = TFT_eSPI();                      
CST820 touch(I2C_SDA, I2C_SCL, TP_RST, TP_INT); 

void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.pushImageDMA(area->x1, area->y1, w, h, (uint16_t *)color_p);

    lv_display_flush_ready(disp);
}


void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    bool touched;
    uint8_t gesture;
    uint16_t touchX, touchY;

    touched = touch.getTouch(&touchX, &touchY, &gesture);

    if (!touched)
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    else
    {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = SCREEN_WIDTH - 1 - touchX;
        data->point.y = SCREEN_HEIGHT - 1 - touchY;
    }
}

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

void my_log_cb(lv_log_level_t level, const char *buf)
{
    Serial.printf(buf);
}

void setupWifi()
{
    WiFi.begin(ssid, password);

    Serial.print("Connecting");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    if (attempts >= 30)
    {
        Serial.println("\nFailed to connect to Wi-Fi after 30 attempts.");
    }
}

void setup()
{
    String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    Serial.begin(115200);
    Serial.println(LVGL_Arduino);
    lv_log_register_print_cb(my_log_cb);

    // Start LVGL
    lv_init();

    // Setup tft
    pinMode(27, OUTPUT);
    digitalWrite(27, LOW);
    tft.begin();        
    tft.setRotation(0); 
    tft.initDMA();      
    tft.fillScreen(TFT_BLACK);

    touch.begin(); 
    digitalWrite(27, HIGH);

    lv_display_t *disp;
    disp = lv_tft_espi_create(screenWidth, screenHeight, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

    lv_indev_t *indev = lv_indev_create();          
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER); 
    lv_indev_set_read_cb(indev, my_touchpad_read);   
    lv_indev_set_disp(indev, disp);

    lv_theme_t *theme = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              true, LV_FONT_DEFAULT);
    lv_disp_set_theme(disp, theme);

    load_preferences();

    ui_graph_screen_init();
    ui_currtime_screen_init();
    ui_weather_screen_init();
    ui_status_screen_init();
    ui_settings_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_graph);

    setupWifi();
    initiateNTPTimeSync(); 
    initBinanceWebSocket();

    binance_candle_stick_create(ui_graph);
}

void updateBitcoinUI(float btcRate, float highRate, float lowRate)
{
    if (btcRate < 1)
    {
        lv_label_set_text_fmt(ui_cryptovalue, "%.2e", btcRate);
    }
    else
    {
        lv_label_set_text_fmt(ui_cryptovalue, "%.1f", btcRate);
    }

    if (lowRate < 1)
    {
        lv_label_set_text_fmt(ui_cryptohigh, "%.2e", lowRate);
    }
    else
    {
        lv_label_set_text_fmt(ui_cryptohigh, "%.1f", lowRate);
    }

    if (highRate < 1)
    {
        lv_label_set_text_fmt(ui_cryptolow, "%.2e", highRate);
    }
    else
    {
        lv_label_set_text_fmt(ui_cryptolow, "%.1f", highRate);
    }
}

void updateTimeAndDate()
{
    time_t now = time(nullptr);
    struct tm *timeInfo = localtime(&now);

    char timeStr[10];
    strftime(timeStr, sizeof(timeStr), "%H:%M", timeInfo);

    char dateStr[12];
    strftime(dateStr, sizeof(dateStr), "%d-%m", timeInfo);

    lv_label_set_text(ui_time, timeStr);
    lv_label_set_text(ui_time1, timeStr);
    lv_label_set_text(ui_time2, timeStr);
    lv_label_set_text(ui_time3, timeStr);
    lv_label_set_text(ui_day, dateStr);
    lv_label_set_text(ui_day1, dateStr);
    lv_label_set_text(ui_day2, dateStr);
    lv_label_set_text(ui_day3, dateStr);
}


void loop()
{
    lv_task_handler(); 
    lv_tick_inc(5);    
    delay(5);          

    if (millis() - lastTimeUpdate > CHECK_TIME_EVERY_X_MS)
    {
        updateTimeAndDate();
        lastTimeUpdate = millis();
    }

    handleBinanceWebSocket();

    if (startup)
    {
        start_chart_updates(7200000);
        start_weather_updates(3600000);
        update_weather_ui();
        update_chart();
        startup = false;
    }
}
