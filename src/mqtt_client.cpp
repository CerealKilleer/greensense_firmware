#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "esp_wifi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "certificades.hpp"
#include "mqtt_client.h"
#include "secrets.hpp"

///@brief Cliente WiFi seguro
WiFiClientSecure client;

///@brief conexión al broker MQTT
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);

///@brief feeds de adafruit IO
Adafruit_MQTT_Publish temper_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish air_hum_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/amb-humidity");
Adafruit_MQTT_Publish lux_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/luxometer");
Adafruit_MQTT_Publish sen0114_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/sen0114");
Adafruit_MQTT_Publish pump_sensor = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/pump");

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

void mqtt_client_init(const char *ssid, const char* password)
{
    wifi_init(ssid, password);
    client.setCACert(CERTIFICATE);
    mqtt_connect();
}