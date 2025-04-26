#ifndef __LIB_PUMP_LEVEL_HPP__
#define __LIB_PUMP_LEVEL_HPP__
#include <Arduino.h>

/**
 * @brief Inicializa el sensor de nivel de la bomba configurando el pin como entrada digital.
 * 
 * @param pin_sensor Número de pin donde está conectado el sensor.
 */
void pump_level_sensor_init(uint8_t pin_sensor);

/**
 * @brief Lee el estado actual del sensor de nivel de la bomba.
 * 
 * @param pin_sensor Número de pin donde está conectado el sensor.
 * @return uint8_t Estado del pin: 
 *         - 0 si está en nivel bajo (LOW).
 *         - 1 si está en nivel alto (HIGH).
 */
uint8_t pump_level_sensor_get(uint8_t pin_sensor);
#endif