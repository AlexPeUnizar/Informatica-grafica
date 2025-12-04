/**
 * @file PPM.hpp
 * @brief Definicion de la clase PPM para la manipulacion de imágenes en formato PPM.
 * 
 * Esta cabecera declara la clase PPM, que permite cargar, guardar y manipular imágenes
 * en formato Portable Pixmap (PPM). Incluye funcionalidades para acceder y modificar
 * pixeles, asi como operaciones de procesamiento de imagen como clamping, ecualizacion
 * y correccion gamma.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef PPM_HPP
#define PPM_HPP
#include <iostream>
#include <memory>
#include <vector>
#include "Color.hpp"

/**
 * @class PPM
 * @brief Clase que representa una imagen en formato PPM (Portable Pixmap).
 * 
 * Esta clase permite cargar imágenes desde archivos PPM, manipular sus pixeles y guardarlas de nuevo.
 * Tambien incluye funciones para aplicar transformaciones como clamping, ecualizacion y correccion gamma.
 */
class PPM{
public:
    /** 
     * @struct Pixel
     * @brief Estructura que representa un pixel en la imagen PPM.
     * 
     * Cada pixel contiene valores de color rojo, verde y azul (r, g, b) como componentes de tipo double.
     * Permite crear pixeles a partir de un objeto Color o directamente con valores RGB.
     */
    struct Pixel{
        double r, g, b;
        Pixel(Color color){
            this->r = color.r;
            this->g = color.g;
            this->b = color.b;
        }
        Pixel(double r, double g, double b){
            this->r = r;
            this->g = g;
            this->b = b;
        }
    };
private:    
    std::string fileName;
    std::string version;
    double realMaxColorValue;
    int32_t height, width;
    double maxColorValue;    
    std::vector<std::vector<std::shared_ptr<Pixel>>> pixels;

private:
    double toMemoryValue(double s);
    double toFileValue(double v);

public:
    PPM(const std::string& fileName);
    PPM() = default;
    PPM(int32_t height, int32_t width);
    ~PPM();

    void load(const std::string& fileName);
    void save(const std::string& fileName = "out.ppm");
    std::vector<std::shared_ptr<Pixel>>& operator[](std::size_t idx){ return pixels[idx]; }
    const std::vector<std::shared_ptr<Pixel>>& operator[](std::size_t idx) const{ return pixels[idx]; }
    friend std::ostream& operator<<(std::ostream& os, const PPM& image);

    friend void clamping(PPM& image, double clampValue);
    friend void equalization(PPM& image);
    friend void equalizationAndClamping(PPM& image, const double clampValue);
    friend void gamma(PPM& image, double gammaValue);
    friend void gammaAndClamping(PPM& image, double gammaValue, double clampValue);  
};


#endif /*PPM_HPP*/