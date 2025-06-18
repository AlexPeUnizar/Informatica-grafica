/**
 * @file ToneMapping.cpp
 * @brief Implementación de funciones para el mapeo de tonos en imágenes PPM.
 *
 * Este archivo contiene las funciones necesarias para realizar operaciones de mapeo de tonos,
 * como clamping, ecualización y corrección gamma sobre imágenes en formato PPM.
 * Las funciones permiten ajustar los valores de color de los píxeles para mejorar la visualización
 * y adaptar el rango dinámico de la imagen.
 *
 * @author Alex
 * @date 18-6-2025
 */
#include "ToneMapping.hpp"
#include <algorithm>
#include <math.h>

/**
 * @brief Aplica clamping a los valores de color de los píxeles de una imagen PPM.
 *
 * Esta función recorre todos los píxeles de la imagen y limita sus valores de color (rojo, verde, azul)
 * al valor máximo especificado por clampValue. Si un valor de color excede clampValue, se ajusta a este valor.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará el clamping.
 * @param clampValue Valor máximo al que se limitarán los valores de color de los píxeles.
 */
void clamping(PPM& image, double clampValue){
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = std::min(clampValue, pixel.get()->r);
            pixel.get()->g = std::min(clampValue, pixel.get()->g);
            pixel.get()->b = std::min(clampValue, pixel.get()->b);
        }
    }
    image.maxColorValue = 255;
    image.realMaxColorValue = clampValue;
}

/**
 * @brief Aplica ecualización a los valores de color de los píxeles de una imagen PPM.
 *
 * Esta función normaliza los valores de color de cada píxel dividiendo por el valor máximo real de color
 * de la imagen, ajustando así los valores al rango [0, 1]. Después, establece el valor máximo de color
 * de la imagen a 255.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la ecualización.
 */
void equalization(PPM& image){
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = (((pixel.get()->r) * 1.0) / (image.realMaxColorValue));
            pixel.get()->g = (((pixel.get()->g) * 1.0) / (image.realMaxColorValue));
            pixel.get()->b = (((pixel.get()->b) * 1.0) / (image.realMaxColorValue));
        }
    }
    image.maxColorValue = 255;
}

/**
 * @brief Aplica ecualización y clamping a los valores de color de los píxeles de una imagen PPM.
 *
 * Esta función primero aplica clamping a los valores de color de los píxeles, limitándolos al valor especificado por clampValue.
 * Luego, normaliza los valores de color dividiendo por el valor máximo real de color de la imagen, ajustando así los valores al rango [0, clampValue].
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la ecualización y clamping.
 * @param clampValue Valor máximo al que se limitarán los valores de color de los píxeles antes de la ecualización.
 */
void equalizationAndClamping(PPM& image, double clampValue){
    //V = image.toMemoryValue(V);
    clamping(image, clampValue);
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = (((pixel.get()->r) * clampValue) / (image.realMaxColorValue));
            pixel.get()->g = (((pixel.get()->g) * clampValue) / (image.realMaxColorValue));
            pixel.get()->b = (((pixel.get()->b) * clampValue) / (image.realMaxColorValue));
        }
    }
}

/**
 * @brief Aplica corrección gamma a los valores de color de los píxeles de una imagen PPM.
 *
 * Esta función primero aplica ecualización a los valores de color de los píxeles, normalizándolos al rango [0, 1].
 * Luego, ajusta cada componente de color (rojo, verde, azul) aplicando la corrección gamma inversa,
 * elevando cada componente a la potencia de 1/gammaValue.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la corrección gamma.
 * @param gammaValue Valor del exponente gamma para la corrección.
 */
void gamma(PPM& image, double gammaValue){
    equalization(image);

    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            
            pixel.get()->r = std::pow(pixel.get()->r, 1 / gammaValue);
            pixel.get()->g = std::pow(pixel.get()->g, 1 / gammaValue);
            pixel.get()->b = std::pow(pixel.get()->b, 1 / gammaValue);
        }
    }
    
    image.maxColorValue = 255;
}

/**
 * @brief Aplica corrección gamma y clamping a los valores de color de los píxeles de una imagen PPM.
 *
 * Esta función primero aplica clamping a los valores de color de los píxeles, limitándolos al valor especificado por clampValue.
 * Luego, aplica la corrección gamma a los valores de color, ajustando cada componente de color (rojo, verde, azul) elevando a la potencia de 1/gammaValue.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la corrección gamma y clamping.
 * @param gammaValue Valor del exponente gamma para la corrección.
 * @param clampValue Valor máximo al que se limitarán los valores de color de los píxeles antes de la corrección gamma.
 */
void gammaAndClamping(PPM& image, double gammaValue, double clampValue){
    clamping(image, clampValue);
    gamma(image, gammaValue);
}