/**
 * @file Light.hpp
 * @brief Declaracion de la clase Light para la gestion de fuentes de luz en la escena.
 * 
 * Este archivo contiene la definicion de la clase Light, que representa una fuente de luz
 * caracterizada por su posicion (centro) y su potencia (color e intensidad).
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "Point.hpp"
#include "Color.hpp"

/**
 * @brief Clase Light que representa una fuente de luz en la escena.
 * 
 * Esta clase almacena la posicion del centro de la luz y su potencia (color e intensidad).
 * Proporciona metodos para obtener estas propiedades.
 */
class Light{
private:
    Point center;
    Color power;
public:
    Light(const Point& center, const Color& power);
    Light();
    ~Light() = default;
    Point getCenter() const;
    Color getPower() const;
    double intensity() const;
};

#endif /* LIGHT_HPP */