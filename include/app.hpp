/**
 * @file app.hpp
 * @brief Declaraciones de funciones principales de la aplicación.
 *
 * Este archivo contiene las funciones de inicialización y ejecución principal
 * de la aplicación embebida. Debe incluirse en el archivo principal del programa.
 */

#ifndef __APP_HPP__
#define __APP_HPP__
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