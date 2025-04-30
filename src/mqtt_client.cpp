/**
 * @file mqtt_client.cpp
 * @brief Módulo de cliente MQTT para publicar y suscribirse a datos de sensores en Adafruit IO.
 * 
 * Este módulo inicializa una conexión WiFi segura, configura el cliente MQTT,
 * publica datos de sensores y gestiona la recepción de comandos a través de un feed MQTT.
 */

 #include <Arduino.h>
 #include <WiFi.h>
 #include <WiFiClientSecure.h>
 #include "esp_wifi.h"
 #include "Adafruit_MQTT.h"
 #include "Adafruit_MQTT_Client.h"
 #include "certificades.hpp"
 #include "mqtt_client.h"
 #include "secrets.hpp"
 #include "greensense_types.hpp"
 
 /// @brief Cliente WiFi seguro para conexiones TLS
 WiFiClientSecure client;
 
 /// @brief Cliente MQTT configurado para Adafruit IO
 Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);
 
 /// @brief Feed para temperatura
 Adafruit_MQTT_Publish temper_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/temperature");
 
 /// @brief Feed para humedad ambiental
 Adafruit_MQTT_Publish air_hum_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/amb-humidity");
 
 /// @brief Feed para nivel de luz (luxómetro)
 Adafruit_MQTT_Publish lux_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/luxometer");
 
 /// @brief Feed para humedad del suelo (sensor SEN0114)
 Adafruit_MQTT_Publish sen0114_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/sen0114");
 
 /// @brief Feed para estado de la bomba
 Adafruit_MQTT_Publish pump_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/pump");
 
 /// @brief Feed de control del actuador (entrada)
 Adafruit_MQTT_Subscribe actuator = Adafruit_MQTT_Subscribe(&mqtt, IO_USERNAME "/feeds/actuator", MQTT_QOS_1);
 
 /**
  * @brief Callback para el feed del actuador.
  * 
  * Recibe un valor y activa una bandera para encender o apagar la bomba.
  * 
  * @param data Cadena recibida del feed.
  * @param len Longitud de la cadena.
  */
 static void pump_init(char *data, uint16_t len)
 {
     if (strcmp("1", data))
         green_sense_flags.turn_on_pump = true;
     else if (strcmp("2", data))
         green_sense_flags.turn_off_pump = true;
 }
 
 /**
  * @brief Inicializa la conexión WiFi con el modo estación.
  * 
  * Intenta conectarse a la red especificada y muestra la IP una vez conectado.
  * 
  * @param ssid Nombre de la red WiFi.
  * @param password Contraseña de la red WiFi.
  */
 static void wifi_init(const char *ssid, const char* password)
 {
     WiFi.mode(WIFI_STA);
     esp_wifi_set_max_tx_power(40);
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
         Serial.print("WiFi.status(): ");
         Serial.print(WiFi.status());
         Serial.print("\n");
         delay(500);
     }
     Serial.println("\nConectado a WiFi :)");
     Serial.print("Dirección IP: ");
     Serial.print(WiFi.localIP());
 }
 
 /**
  * @brief Establece conexión con el broker MQTT si aún no está conectado.
  * 
  * @return true si la conexión fue exitosa, false en caso contrario.
  */
 static bool mqtt_connect() 
 {
     int8_t ret;
   
     if (mqtt.connected())
         return true;
   
     Serial.print("\nMQTT: conectando... ");
   
     if ((ret = mqtt.connect()) != 0) { 
          Serial.println(mqtt.connectErrorString(ret));
          Serial.println("MQTT: no se pudo conectar :c");
          mqtt.disconnect();
          return false;
     }
   
     Serial.println("MQTT conectado!");
     return true;
 }
 
 /**
  * @brief Publica los valores de sensores en sus respectivos feeds MQTT.
  * 
  * @param temp Temperatura en grados Celsius.
  * @param amb_hum Humedad ambiental en porcentaje.
  * @param luxometer Nivel de luz ambiental (lux).
  * @param sen0114 Humedad del suelo desde el sensor SEN0114.
  * @param pump_level Estado de la bomba (0 = apagada, 1 = encendida).
  */
 void mqtt_publish_sensors(float temp, float amb_hum, float luxometer, 
                           float sen0114, uint8_t pump_level)
 {
     if(!mqtt_connect())
         return;
     temper_sensor.publish(temp);
     air_hum_sensor.publish(amb_hum);
     lux_sensor.publish(luxometer);
     sen0114_sensor.publish(sen0114);
     pump_sensor.publish(pump_level);
     Serial.println("Publicado");
 }
 
 /**
  * @brief Inicializa el cliente MQTT y la conexión WiFi.
  * 
  * Configura el cliente TLS, suscribe al feed del actuador y establece la conexión inicial.
  * 
  * @param ssid Nombre de la red WiFi.
  * @param password Contraseña de la red WiFi.
  */
 void mqtt_client_init(const char *ssid, const char* password)
 {
     wifi_init(ssid, password);
     client.setCACert(CERTIFICATE);
     actuator.setCallback(pump_init);
     mqtt.subscribe(&actuator);
     mqtt_connect();
 }
 
 /**
  * @brief Procesa paquetes entrantes del broker MQTT (comandos).
  * 
  * Debe llamarse regularmente en el bucle principal para recibir datos.
  */
 void mqtt_incoming_data(void)
 {
     mqtt.processPackets(50);
 }
 