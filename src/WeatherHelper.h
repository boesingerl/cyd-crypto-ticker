#ifndef WEATHER_HELPER_H
#define WEATHER_HELPER_H

#include <map>
#include <string>
#include <lvgl.h>

// Define the weather API URL
#define WEATHER_API_URL "https://api.open-meteo.com/v1/forecast?latitude=" + String(latitude) + "&longitude=" + String(longitude) + "&current=apparent_temperature,weather_code"

// Map to convert weather codes to characters
extern std::map<std::string, char> id_to_char;

// Structure to hold weather data
typedef struct
{
    float apparent_temperature;
    int weather_code;
} weather_t;

// Function declarations
bool fetch_weather_data(weather_t *weather);
void update_weather_ui();
void start_weather_updates(uint32_t update_interval_ms);
void stop_weather_updates();

#endif // WEATHER_HELPER_H
