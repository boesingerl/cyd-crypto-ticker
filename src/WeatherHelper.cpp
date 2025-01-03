#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <map>
#include <string>
#include <lvgl.h>

#include "ui.h"
#include "WeatherHelper.h"


std::map<std::string, char> id_to_char = {
    {"0", 'N'},  // Sunny
    {"1", 'C'},  // Mainly Sunny
    {"2", 'P'},  // Partly Cloudy
    {"3", 'O'},  // Cloudy
    {"45", 'F'}, // Foggy
    {"48", 'F'}, // Rime Fog
    {"51", 'M'}, // Light Drizzle
    {"53", 'M'}, // Drizzle
    {"55", 'M'}, // Heavy Drizzle
    {"56", 'M'}, // Light Freezing Drizzle
    {"57", 'M'}, // Freezing Drizzle
    {"61", 'M'}, // Light Rain
    {"63", 'M'}, // Rain
    {"65", 'M'}, // Heavy Rain
    {"66", 'M'}, // Light Freezing Rain
    {"67", 'M'}, // Freezing Rain
    {"71", 'D'}, // Light Snow
    {"73", 'D'}, // Snow
    {"75", 'D'}, // Heavy Snow
    {"77", 'D'}, // Snow Grains
    {"80", 'M'}, // Light Showers
    {"81", 'M'}, // Showers
    {"82", 'M'}, // Heavy Showers
    {"85", 'D'}, // Light Snow Showers
    {"86", 'D'}, // Snow Showers
    {"95", 'A'}, // Thunderstorm
    {"96", 'A'}, // Light Thunderstorms With Hail
    {"99", 'A'}  // Thunderstorm With Hail
};

// Structure to hold weather data
typedef struct
{
    float apparent_temperature;
    int weather_code;
} weather_t;

// Fetch current weather data from Open-Meteo API
bool fetch_weather_data(weather_t *weather)
{
    HTTPClient http;
    http.begin(WEATHER_API_URL);

    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK)
    {
        Serial.printf("HTTP GET failed, code: %d\n", httpCode);
        http.end();
        return false;
    }

    String payload = http.getString();

    DynamicJsonDocument doc(1024); // Allocate memory for the dynamic JSON document

    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        http.end();
        return false;
    }

    JsonObject current_weather = doc["current"];
    weather->apparent_temperature = current_weather["apparent_temperature"].as<float>();
    weather->weather_code = current_weather["weather_code"].as<int>();

    http.end();
    return true;
}

static lv_timer_t *weather_update_timer = NULL;

void update_weather_ui()
{
    weather_t current_weather;
    if (!fetch_weather_data(&current_weather))
    {
        Serial.println("Failed to fetch weather data from Open-Meteo.");
        return;
    }

    // Update temperature label
    char temp_str[8];
    snprintf(temp_str, sizeof(temp_str), "%.0fC", current_weather.apparent_temperature);
    lv_label_set_text(ui_temperature, temp_str);

    // Update weather icon label
    char weather_code_str[4];
    snprintf(weather_code_str, sizeof(weather_code_str), "%d", current_weather.weather_code);
    char weather_icon = id_to_char[weather_code_str];
    char icon_str[2] = {weather_icon, '\0'};
    lv_label_set_text(ui_weatherindicator, icon_str);
}

void start_weather_updates(uint32_t update_interval_ms)
{
    if (weather_update_timer == NULL)
    {
        weather_update_timer = lv_timer_create([](lv_timer_t *timer)
                                               { update_weather_ui(); }, update_interval_ms, NULL);
    }
}

void stop_weather_updates()
{
    if (weather_update_timer != NULL)
    {
        lv_timer_del(weather_update_timer);
        weather_update_timer = NULL;
    }
}
