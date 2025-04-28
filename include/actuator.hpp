#ifndef __ACTUATOR_HPP__
#define __ACTUATOR_HPP__
#include <Arduino.h>

/// @brief Inicializa el pin de salida para la bomba
/// @param actuator_pin Pin de salida para la bomba

void actuator_init(uint8_t actuator_pin);

/// @brief Activa o desactiva el pin de la bomba
/// @param action acción para la bomba
void actuator_act(uint8_t action);
#endif