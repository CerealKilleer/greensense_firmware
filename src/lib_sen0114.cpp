#include <Arduino.h>
#include <math.h>
#include "lib_sen0114.hpp"
#define MAX_HUM_VALUE 2500

static uint16_t sen0114_get_moisture_hum(uint8_t sensor_pin)
{
    return analogRead(sensor_pin);
}

float sen0114_get_moisture_hum_percentage(uint8_t sensor_pin)
{
    float hum = round(100.0*sen0114_get_moisture_hum(sensor_pin)/MAX_HUM_VALUE);
    return hum > 100.0 ? 100.0 : hum;
}