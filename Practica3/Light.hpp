/**
 * @file Light.hpp
 * @brief Declaración de la clase Light para la gestión de fuentes de luz en la escena.
 * 
 * Este archivo contiene la definición de la clase Light, que representa una fuente de luz
 * caracterizada por su posición (centro) y su potencia (color e intensidad).
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
 * Esta clase almacena la posición del centro de la luz y su potencia (color e intensidad).
 * Proporciona métodos para obtener estas propiedades.
 */
class Light{
private:
    Point center;
    Color power;
public:
    Light(const Point& center, const Color& power);
    Light();
    ~Light();
    Point getCenter() const;
    Color getPower() const;
};

#endif /* LIGHT_HPP */