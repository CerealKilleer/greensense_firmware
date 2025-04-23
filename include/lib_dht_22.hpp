#ifndef __LIB_DHT_22_HPP__
#define __LIB_DHT_22_HPP__

/**
 * @brief Inicializa el sensor DHT11.
 * 
 * Debe llamarse una vez antes de realizar lecturas de temperatura o humedad.
 */
void dht_22_init(void);

/**
 * @brief Obtiene la temperatura en grados Celsius desde el DHT11.
 * 
 * @param[out] temp Variable donde se almacenará la temperatura leída.
 * @return true si la lectura fue exitosa, false si falló (valor inválido).
 */
bool dht_22_get_temp(float &temp);

/**
 * @brief Obtiene la humedad relativa en porcentaje desde el DHT11.
 * 
 * @param[out] hum Variable donde se almacenará la humedad leída.
 * @return true si la lectura fue exitosa, false si falló (valor inválido).
 */
bool dht_22_get_humidity(float &hum);
#endif