#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include "lib_bh170.hpp"
#define STD_MODE_FREQ 100000

BH1750 light_meter;

void bh170_init(const uint8_t i2c_addr, const int sda_pin, const int scl_pin)
{
    // Inicializa el bus I2C con los pines y la frecuencia
    Wire.begin(sda_pin, scl_pin, STD_MODE_FREQ);
    // Inicia el sensor con la dirección I2C especificada
    light_meter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, i2c_addr, &Wire);
}

bool bh170_get_lux(float &lux)
{
    float aux_lux = light_meter.readLightLevel();
    
    if (aux_lux < 0)
        return false;

    lux = aux_lux;
    return true;
}