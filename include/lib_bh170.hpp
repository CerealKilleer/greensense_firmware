#ifndef __LIB_BH170_HPP__
#define __LIB_BH170_HPP__
/**
 * @brief Inicializa el sensor BH1750 y el bus I2C en los pines especificados.
 * 
 * @param i2c_addr Dirección I2C del sensor BH1750 (por defecto suele ser 0x23 o 0x5C).
 * @param sda_pin Número de pin GPIO utilizado como SDA.
 * @param scl_pin Número de pin GPIO utilizado como SCL.
 */
void bh170_init(const uint8_t i2c_addr, int sda_pin, int scl_pin);
/**
 * @brief Lee el nivel de luz (lux) desde el sensor BH1750.
 * 
 * @param lux Referencia donde se almacenará el valor medido de luz en lux.
 * @return true Si la lectura fue exitosa y el valor es válido.
 * @return false Si hubo un error o el valor leído es inválido (negativo).
 */
bool bh170_get_lux(float &lux);
#endif