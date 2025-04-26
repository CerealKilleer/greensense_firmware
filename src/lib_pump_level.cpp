#include <Arduino.h>
#include "lib_pump_level.hpp"

void pump_level_sensor_init(uint8_t pin_sensor)
{
    pinMode(pin_sensor, INPUT);
}

uint8_t pump_level_sensor_get(uint8_t pin_sensor)
{
    return digitalRead(pin_sensor);
}