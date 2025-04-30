/**
 * @file lib_lcd162.cpp
 * @brief Control de pantalla LCD 16x2 I2C usando la librería LiquidCrystal_I2C.
 * 
 * Este archivo contiene funciones para inicializar y escribir datos
 * en una pantalla LCD de 16 columnas y 2 filas conectada mediante I2C.
 */

 #include <Arduino.h>
 #include <LiquidCrystal_I2C.h>
 #include "lib_lcd162.hpp"
 
 #define ADDR 0x27       ///< Dirección I2C del LCD
 #define NUM_COLS 16     ///< Número de columnas del LCD
 #define NUM_ROWS 2      ///< Número de filas del LCD
 
 /// Objeto global para el control del LCD
 LiquidCrystal_I2C lcd(ADDR, NUM_COLS, NUM_ROWS);
 
 /**
  * @brief Inicializa el LCD 16x2 y activa la retroiluminación.
  * 
  * Esta función debe llamarse una vez durante la configuración del sistema
  * para preparar el LCD para mostrar información.
  */
 void lcd_162_init(void)
 {
     lcd.init();
     lcd.backlight();
 }
 
 /**
  * @brief Escribe valores de sensores y estado de bomba en el LCD.
  * 
  * Esta función limpia el LCD y muestra en la primera línea la temperatura
  * y la humedad del suelo, y en la segunda línea la luminosidad y el estado
  * de la bomba de riego.
  * 
  * @param temp Temperatura medida (en grados Celsius).
  * @param soil_moist Humedad del suelo (porcentaje).
  * @param lux Nivel de luz ambiental (lux).
  * @param pump_lev Estado de la bomba de riego (1 = encendida, 0 = apagada).
  */
 void lcd_162_write(float temp, float soil_moist, float lux, uint8_t pump_lev)
 {
     lcd.clear();
     lcd.setCursor(0,0);
     String msg = "T:" + String(temp) + " H:" + String(soil_moist);
     lcd.print(msg);
     lcd.setCursor(0,1);
     msg = "Lx:" + String(lux) + " P:" + (pump_lev ? "OFF" : "ON");
     lcd.print(msg);
 }
 