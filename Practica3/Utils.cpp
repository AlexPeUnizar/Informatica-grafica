/**
 * @file Utils.cpp
 * @brief Implementación de funciones utilitarias para generación de números aleatorios.
 * @author Alex
 * @date 18-6-2025
 */
#include "Utils.hpp"
#include <cstdlib>
#include <time.h>

/**
 * @brief Genera un número aleatorio de tipo double en un rango específico.
 * 
 * Esta función genera un número aleatorio entre los valores min y max.
 * 
 * @param min Valor mínimo del rango.
 * @param max Valor máximo del rango.
 * @return double Número aleatorio generado en el rango [min, max].
 */
double randomDouble(double min, double max){
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

/**
 * @brief Genera un número aleatorio de tipo double en el rango [0.0, 1.0].
 * 
 * Esta función es una sobrecarga de la función randomDouble sin parámetros,
 * que devuelve un número aleatorio entre 0.0 y 1.0.
 * 
 * @return double Número aleatorio generado en el rango [0.0, 1.0].
 */
double randomDouble(){
    return randomDouble(0.0, 1.0);
}

