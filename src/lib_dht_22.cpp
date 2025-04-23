/**
 * @file lib_dht_22.cpp
 * @brief Implementación de funciones para manejo del sensor DHT22 usando la librería Adafruit DHT.
 */

#include <Arduino.h>
#include <DHT.h>
#include "lib_dht_22.hpp"
#define DHT_PIN 2
#define ERROR_TEMP -274.0f
#define ERROR_HUMIDITY -1.0f

DHT dht_22(DHT_PIN, DHT22);

void dht_22_init(void)
{
    dht_22.begin();
}

bool dht_22_get_temp(float &temp)
{
    float tmp = dht_22.readTemperature();
    if (isnan(tmp)) {
        temp = ERROR_TEMP;
        return false;
    }
    temp = tmp;
    return true;
}

bool dht_22_get_humidity(float &hum)
{
    float tmp = dht_22.readHumidity();
    if (isnan(tmp)) {
        hum = ERROR_HUMIDITY;
        return false;
    }
    hum = tmp;
    return true;
}