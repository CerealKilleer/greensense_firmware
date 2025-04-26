/**
 * @file app.hpp
 * @brief Declaraciones de funciones principales de la aplicación.
 *
 * Este archivo contiene las funciones de inicialización y ejecución principal
 * de la aplicación embebida. Debe incluirse en el archivo principal del programa.
 */

#ifndef __APP_HPP__
#define __APP_HPP__

///@brief sensor de bomba
#define PUMP_LEVEL_PIN 6

/// @brief SSID del WiFi
#define SSID "Flia_Lopez_Mejia"

/// @brief Password del WiFi
#define PASSWORD "normandiayalgora"

/// @brief Valor no válido cuando los sensores no se pueden leer
#define INVALID_VALUE -1

/// @brief PIN para el sensor de humedad del suelo
#define SEN0114_PIN 13

/// @brief Pines SDA y SCL para el medidor de luz
#define SDA_PIN 47
#define SCL_PIN 20

/// @brief Dirección del sensor 0x23 a tierra, 0x5C a VCC
#define BH170_ADDR 0x23

/// @brief Número de muestras almacenadas para todas las variables
#define SAMPLES 8

/// @brief Tiempo en microsegundos para leer los sensores
#define READ_SENSORS_US (3*(1000000))
#define SEND_SENSORS_US (15*(1000000))
/// @brief Inicializa los periféricos y componentes de la aplicación.
///
/// Esta función configura el entorno de la aplicación, incluyendo la comunicación
/// serial y sensores necesarios.
void app_init(void);
/// @brief Ejecuta el ciclo principal de la aplicación.
///
/// Esta función se llama repetidamente en el bucle principal (`loop()` en Arduino).
/// Se encarga de gestionar las tareas principales del sistema.
void app_main(void);
#endif