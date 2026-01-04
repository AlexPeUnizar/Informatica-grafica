/**
 * @file ToneMapping.hpp
 * @brief Declaraciones de funciones para la aplicacion de tecnicas de tone mapping sobre imágenes en formato PPM.
 *
 * Este archivo contiene las declaraciones de las funciones necesarias para realizar operaciones de clamping,
 * ecualizacion y correccion gamma sobre imágenes, asi como combinaciones de estas tecnicas. 
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
