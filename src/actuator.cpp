#include <Arduino.h>
#include "actuator.hpp"

uint8_t act_pin;

void actuator_init(uint8_t actuator_pin)
{   
    act_pin = actuator_pin;
    pinMode(actuator_pin, OUTPUT);
}

void actuator_act(uint8_t action)
{
    digitalWrite(act_pin, action);
}