#ifndef __LIB_SEN0114_HPP__
#define __LIB_SEN0114_HPP__
#include <Arduino.h>
/**
 * @brief Calcula el porcentaje de humedad basado en el valor del sensor SEN0114.
 *
 * El valor se invierte para que 0% represente suelo seco y 100% suelo húmedo.
 *
 * @param sensor_pin Pin analógico donde está conectado el sensor.
 * @return Porcentaje de humedad (0–100%).
 */
float sen0114_get_moisture_hum_percentage(uint8_t sensor_pin);
#endif