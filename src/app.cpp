#include <Arduino.h>
#include "lib_dht_22.hpp"
#include "circular_array.hpp"
#include "lib_bh170.hpp"
#include "lib_sen0114.hpp"
#include "esp_timer.h"
#include "esp_sleep.h"

/// @brief Valor no válido cuando los sensores no se pueden leer
#define INVALID_VALUE -1

/// @brief PIN para el sensor de humedad del suelo
#define SEN0114_PIN 13

/// @brief Pines SDA y SCL para el medidor de luz
#define SDA_PIN 21
#define SCL_PIN 20

/// @brief Dirección del sensor 0x23 a tierra, 0x5C a VCC
#define BH170_ADDR 0x23

/// @brief Número de muestras almacenadas para todas las variables
#define SAMPLES 8

/// @brief Tiempo en microsegundos para leer los sensores
#define READ_SENSORS_US (3*(1000000))
#define SEND_SENSORS_US (10*(1000000))

/// @brief Array circular para almacenar muestras de temperatura
circular_array<float, SAMPLES> env_temps;

/// @brief Array circular para almacenar muestras de humedad
circular_array<float, SAMPLES> air_humidities;

/// @brief Array circular para almacenar muestras intensidad de luz
circular_array<float, SAMPLES> luxometer;

/// @brief Array circular para almacenar muestras de humedad del suelo
circular_array<float, SAMPLES> sen0114;

/// @brief Estructura de banderas para controlar el estado del sistema
typedef union {
    uint8_t flags; ///< Byte completo de flags
    struct {
        bool read_sensors : 1; ///< Bandera que indica cuándo leer sensores
        bool send_sensors : 1;
        uint8_t : 6; ///< Relleno de bits no utilizados
    };
} flags_t; 

/// @brief Instancia global de banderas del sistema
volatile flags_t green_sense_flags;

/// @brief Callback del temporizador que activa la lectura de sensores
/// @param args Argumentos pasados al callback (no utilizados)
static void read_sensors_timer(void* args)
{
    green_sense_flags.read_sensors = true;
}

/// @brief Callback del temporizador que activa el envio de informacion de sensores
/// @param args Argumentos pasados al callback (no utilizados)
static void send_sensors_timer(void* args)
{
    green_sense_flags.send_sensors = true;
}

/// @brief Inicializa el temporizador periódico que activa la lectura de sensores
static void init_read_sensors_timer(void)
{
    esp_timer_create_args_t read_timer_cfg = {
        .callback = &read_sensors_timer,
        .arg = nullptr,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "periodic"
    };

    esp_timer_handle_t read_sensor_timer;
    esp_timer_create(&read_timer_cfg, &read_sensor_timer);
    esp_timer_start_periodic(read_sensor_timer, READ_SENSORS_US);
}

/// @brief Inicializa el temporizador periódico que activa el envio de informacion de sensores
static void init_send_sensors_timer(void)
{
    esp_timer_create_args_t send_timer_cfg = {
        .callback = &send_sensors_timer,
        .arg = nullptr,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "periodic"
    };

    esp_timer_handle_t send_sensor_timer;
    esp_timer_create(&send_timer_cfg, &send_sensor_timer);
    esp_timer_start_periodic(send_sensor_timer, SEND_SENSORS_US);
}

/// @brief Lee la temperatura del sensor DHT22 y la almacena en el array `temps`
///
/// Esta función utiliza un índice circular para guardar las últimas `SAMPLES`
/// lecturas de temperatura. Solo guarda el valor si la lectura fue válida.
static void app_read_env_tem(void)
{
    float temp;
    if (dht_22_get_temp(temp))
        env_temps.add_value(temp);
    else
        env_temps.add_value(INVALID_VALUE);
}

/// @brief Lee la humedad del sensor DHT22 y la almacena en el array `humidities`
///
/// Esta función utiliza un índice circular para guardar las últimas `SAMPLES`
/// lecturas de humedad. Solo guarda el valor si la lectura fue válida.
static void app_read_air_hum(void)
{
    float hum;
    if (dht_22_get_humidity(hum))
        air_humidities.add_value(hum);
    else
        air_humidities.add_value(INVALID_VALUE);
}

/// @brief Lee la cantidad de luz del sensor BH170 y la almacena en el array `luxometer`
///
/// Esta función utiliza un índice circular para guardar las últimas `SAMPLES`
/// lecturas de cantidad de luz. Solo guarda el valor si la lectura fue válida.
static void app_read_luxometer(void)
{
    float lux;
    if (bh170_get_lux(lux))
        luxometer.add_value(lux);
    else
        luxometer.add_value(INVALID_VALUE);   
}

/// @brief Lee la cantidad de luz del sensor BH170 y la almacena en el array `luxometer`
///
/// Esta función utiliza un índice circular para guardar las últimas `SAMPLES`
/// lecturas de cantidad de luz. Solo guarda el valor si la lectura fue válida.
static void app_read_sen0114(void)
{
    sen0114.add_value(sen0114_get_moisture_hum_percentage(SEN0114_PIN));
}

/// @brief Inicializa el sistema de la aplicación
///
/// Configura la comunicación serial y los sensores
void app_init(void)
{
    Serial.begin(115200);
    dht_22_init();
    bh170_init(BH170_ADDR, SDA_PIN, SCL_PIN);
    init_read_sensors_timer();
    init_send_sensors_timer();
}

/// @brief Función principal del programa
///
/// Esta función se ejecuta continuamente desde el `loop()` de Arduino.
void app_main(void)
{
    while(green_sense_flags.flags) {
        if (green_sense_flags.read_sensors) {
            app_read_env_tem();
            app_read_air_hum();
            app_read_luxometer();
            app_read_sen0114();
            green_sense_flags.read_sensors = false;
        }
        if (green_sense_flags.send_sensors) {
            Serial.println("Temperatura: [°C]" + String(env_temps.get_mean_value()));
            Serial.println("Humedad del aire [%]: " + String(air_humidities.get_mean_value()));
            Serial.println("Luz [lux]: " + String(luxometer.get_mean_value()));
            Serial.println("Humedad del suelo [%]" + String(sen0114.get_mean_value()));
            green_sense_flags.send_sensors = false;
        }
    }
}
