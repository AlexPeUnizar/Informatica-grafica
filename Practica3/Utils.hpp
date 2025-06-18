/**
 * @file Utils.hpp
 * @brief Declaraciones de utilidades para generación de números aleatorios.
 * 
 * Este archivo contiene las declaraciones de funciones auxiliares para la generación de números aleatorios
 * en un rango determinado o en el rango por defecto.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <cstdint>
/* SETTINGS */

const size_t MAX_BOUNCES = 6;
const size_t MAX_PATHS = 1;

const size_t MAX_RAYS_PER_PIXEL = 512;
const size_t IMAGE_WIDTH = 1024;
const size_t IMAGE_HEIGHT = 1024;

/* FUNCTIONS */
double randomDouble(double min, double max);
double randomDouble();

#endif /* UTILS_HPP */