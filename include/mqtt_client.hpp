#ifndef __MQTT_CLIENT_HPP__
#define __MQTT_CLIENT_HPP__

/// @brief Inicializa el cliente MQTT
/// @param ssid El nombre de la red WiFi
/// @param password La contraseña de la red WiFi
/**
 * @brief Publica el valor de temperatura en el feed de Adafruit IO.
 *
 * Esta función envía el valor de temperatura (float) al feed de temperatura de Adafruit IO
 * utilizando la instancia de MQTT previamente configurada.
 *
 * @param temp Valor de la temperatura a publicar.
 * @param amb_hum Valor de la humedad ambiental a publicar
 * @param luxometer Valor de intensidad de luz
 * @param sen0114 Valor de humedad del suelo
 * @param pump_level Valor del nivel de la bomba de agua
 * @note Esta función utiliza el feed previamente configurado con la ruta /feeds/temperature
 *       y requiere que el cliente MQTT esté conectado.
 */
void mqtt_publish_sensors(float temp, float amb_hum, 
                            float luxometer, float sen0114,
                            uint8_t pump_level);

                            /**
 * @brief Inicializa el cliente MQTT
 *
 * @param ssid SSID del WiFi
 * @param password Password del WiFi
 */

void mqtt_client_init(const char *ssid, const char* password);
#endif