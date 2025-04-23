#ifndef __CIRCULAR_ARRAY_HPP__
#define __CIRCULAR_ARRAY_HPP__
#include <cstddef>
template <typename T, size_t size>
class circular_array {
    private:
        T buffer[size];
        size_t index;
    public:
        circular_array() : index(0) {
            for (size_t i = 0; i < size; i++)
                buffer[i] = T();
        }

        /// @brief Añade un nuevo valor al buffer
        void add_value(T value) {
            buffer[index] = value;
            index = (index + 1) % size;
        }

        /// @brief Calcula el promedio de todas las muestras
        T get_mean_value(void) {
            T sum = T();
            for (size_t i = 0; i < size; i++) {
                sum += buffer[i];
            }
            return sum / size;
        }
};

#endif