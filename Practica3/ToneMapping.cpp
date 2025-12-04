/**
 * @file ToneMapping.cpp
 * @brief Implementacion de funciones para el mapeo de tonos en imágenes PPM.
 *
 * Este archivo contiene las funciones necesarias para realizar operaciones de mapeo de tonos,
 * como clamping, ecualizacion y correccion gamma sobre imágenes en formato PPM.
 * Las funciones permiten ajustar los valores de color de los pixeles para mejorar la visualizacion
 * y adaptar el rango dinámico de la imagen.
 *
 * @author Alex
 * @date 18-6-2025
 */
#include "ToneMapping.hpp"
#include <algorithm>
#include <math.h>

/**
 * @brief Aplica clamping a los valores de color de los pixeles de una imagen PPM.
 *
 * Esta funcion recorre todos los pixeles de la imagen y limita sus valores de color (rojo, verde, azul)
 * al valor máximo especificado por clampValue. Si un valor de color excede clampValue, se ajusta a este valor.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará el clamping.
 * @param clampValue Valor máximo al que se limitarán los valores de color de los pixeles.
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
 * @brief Aplica ecualizacion a los valores de color de los pixeles de una imagen PPM.
 *
 * Esta funcion normaliza los valores de color de cada pixel dividiendo por el valor máximo real de color
 * de la imagen, ajustando asi los valores al rango [0, 1]. Despues, establece el valor máximo de color
 * de la imagen a 255.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la ecualizacion.
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
 * @brief Aplica ecualizacion y clamping a los valores de color de los pixeles de una imagen PPM.
 *
 * Esta funcion primero aplica clamping a los valores de color de los pixeles, limitándolos al valor especificado por clampValue.
 * Luego, normaliza los valores de color dividiendo por el valor máximo real de color de la imagen, ajustando asi los valores al rango [0, clampValue].
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la ecualizacion y clamping.
 * @param clampValue Valor máximo al que se limitarán los valores de color de los pixeles antes de la ecualizacion.
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
 * @brief Aplica correccion gamma a los valores de color de los pixeles de una imagen PPM.
 *
 * Esta funcion primero aplica ecualizacion a los valores de color de los pixeles, normalizándolos al rango [0, 1].
 * Luego, ajusta cada componente de color (rojo, verde, azul) aplicando la correccion gamma inversa,
 * elevando cada componente a la potencia de 1/gammaValue.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la correccion gamma.
 * @param gammaValue Valor del exponente gamma para la correccion.
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
 * @brief Aplica correccion gamma y clamping a los valores de color de los pixeles de una imagen PPM.
 *
 * Esta funcion primero aplica clamping a los valores de color de los pixeles, limitándolos al valor especificado por clampValue.
 * Luego, aplica la correccion gamma a los valores de color, ajustando cada componente de color (rojo, verde, azul) elevando a la potencia de 1/gammaValue.
 *
 * @param image Referencia a la imagen PPM sobre la que se aplicará la correccion gamma y clamping.
 * @param gammaValue Valor del exponente gamma para la correccion.
 * @param clampValue Valor máximo al que se limitarán los valores de color de los pixeles antes de la correccion gamma.
 */
void gammaAndClamping(PPM& image, double gammaValue, double clampValue){
    clamping(image, clampValue);
    gamma(image, gammaValue);
}