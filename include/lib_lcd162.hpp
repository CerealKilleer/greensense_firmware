/**
 * @file lib_lcd162.hpp
 * @brief Declaraciones para el control de un LCD 16x2 vía I2C.
 * 
 * Este archivo contiene las declaraciones de funciones para inicializar
 * y escribir datos en una pantalla LCD 16x2 utilizando la librería 
 * LiquidCrystal_I2C.
 */

 #ifndef __LIB_LCD162_HPP__
 #define __LIB_LCD162_HPP__
 
 #include <Arduino.h>
 
 /**
  * @brief Inicializa el LCD 16x2 y enciende la retroiluminación.
  * 
  * Debe ser llamada durante el setup del programa para preparar el LCD.
  */
 void lcd_162_init(void);
 
 /**
  * @brief Muestra en el LCD los valores de sensores y el estado de la bomba.
  * 
  * Escribe en la primera línea la temperatura y la humedad del suelo, y en
  * la segunda línea la iluminación en lux y el estado de la bomba (encendida o apagada).
  * 
  * @param temp Temperatura en grados Celsius.
  * @param soil_moist Humedad del suelo en porcentaje.
  * @param lux Nivel de luz en lux.
  * @param pump_lev Estado de la bomba (1 = encendida, 0 = apagada).
  */
 void lcd_162_write(float temp, float soil_moist, float lux, uint8_t pump_lev);
 
 #endif // __LIB_LCD162_HPP__
 