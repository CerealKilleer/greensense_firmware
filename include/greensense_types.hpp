#ifndef __GREENSENSE_TYPES_HPP__
#define __GREENSENSE_TYPES_HPP__
#include <Arduino.h>

/// @brief Estructura de banderas para controlar el estado del sistema
typedef union {
    uint8_t flags; ///< Byte completo de flags
    struct {
        bool read_sensors : 1; ///< Bandera que indica cuándo leer sensores
        bool send_sensors : 1;
        bool turn_on_pump : 1;
        bool turn_off_pump : 1;
        uint8_t : 4; ///< Relleno de bits no utilizados
    };
} flags_t; 

/// @brief Instancia global de banderas del sistema
extern volatile flags_t green_sense_flags;

#endif