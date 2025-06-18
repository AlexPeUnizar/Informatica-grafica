/**
 * @file ToneMapping.hpp
 * @brief Declaraciones de funciones para la aplicación de técnicas de tone mapping sobre imágenes en formato PPM.
 *
 * Este archivo contiene las declaraciones de las funciones necesarias para realizar operaciones de clamping,
 * ecualización y corrección gamma sobre imágenes, así como combinaciones de estas técnicas. 
 * Las funciones están diseñadas para trabajar con objetos de la clase PPM.
 *
 * @author Alex
 * @date 18-6-2025
 */
#ifndef TONE_MAPPING_HPP
#define TONE_MAPPING_HPP

#include "PPM.hpp" 

void clamping(PPM& image, double clampValue = 1.0);
void equalization(PPM& image);
void equalizationAndClamping(PPM& image, const double clampValue);
void gamma(PPM& image, double gammaValue);
void gammaAndClamping(PPM& image, double gammaValue, double clampValue = 1.0);

#endif /* TONE_MAPPING_HPP */
