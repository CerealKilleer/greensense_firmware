#ifndef __MQTT_CLIENT_HPP__
#define __MQTT_CLIENT_HPP__

/**
 * @file mqtt_client.hpp
 * @brief Declaraciones para el manejo de comunicación MQTT con Adafruit IO en GreenSense.
 *
 * Proporciona funciones para inicializar el cliente MQTT, publicar datos de sensores,
 * y manejar mensajes entrantes desde los feeds de Adafruit IO.
 */

#include <Arduino.h>

/**
 * @brief Inicializa la conexión WiFi y el cliente MQTT.
 *
 * Configura el módulo en modo estación, establece la conexión TLS,
 * y suscribe al feed del actuador en Adafruit IO.
 *
 * @param ssid Nombre (SSID) de la red WiFi.
 * @param password Contraseña de la red WiFi.
 */
void mqtt_client_init(const char *ssid, const char* password);

/**
 * @brief Publica los datos de sensores al broker MQTT de Adafruit IO.
 *
 * Esta función envía los valores de temperatura, humedad ambiental,
 * luz ambiental (lux), humedad del suelo y estado de la bomba
 * a sus respectivos feeds configurados en Adafruit IO.
 *
 * @param temp Valor de la temperatura (°C).
 * @param amb_hum Valor de la humedad del aire (%).
 * @param luxometer Nivel de luz ambiental (lux).
 * @param sen0114 Humedad del suelo (% o unidad relativa).
 * @param pump_level Estado de la bomba (0 = apagada, 1 = encendida).
 */
void mqtt_publish_sensors(float temp, float amb_hum, 
                          float luxometer, float sen0114,
                          uint8_t pump_level);

/**
 * @brief Procesa los mensajes MQTT entrantes.
 *
 * Debe llamarse regularmente dentro del bucle principal para gestionar comandos desde el broker.
 */
void mqtt_incoming_data(void);


#endif // __MQTT_CLIENT_HPP__