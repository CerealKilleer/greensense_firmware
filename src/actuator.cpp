/**
 * @file actuator.cpp
 * @brief Control de un actuador (como una bomba de riego) usando un pin digital.
 * 
 * Este archivo implementa funciones para inicializar y controlar un actuador
 * digital simple, como una bomba, a través de un pin de salida.
 */

 #include <Arduino.h>
 #include "actuator.hpp"
 
 /// Pin conectado al actuador
 uint8_t act_pin;
 
 /**
  * @brief Inicializa el pin del actuador como salida.
  * 
  * Esta función debe llamarse durante el setup del programa. Configura el pin
  * especificado como salida y lo guarda para su uso posterior.
  * 
  * @param actuator_pin Número del pin de Arduino conectado al actuador.
  */
 void actuator_init(uint8_t actuator_pin)
 {   
     act_pin = actuator_pin;
     pinMode(actuator_pin, OUTPUT);
 }
 
 /**
  * @brief Controla el actuador escribiendo un valor digital en su pin.
  * 
  * @param action Valor digital a escribir (0 para desactivar, 1 para activar).
  */
 void actuator_act(uint8_t action)
 {
     digitalWrite(act_pin, action);
 }
 