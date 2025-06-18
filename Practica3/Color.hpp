
/**
 * @file Color.hpp
 * @brief Definición de la clase Color, que representa un color RGB y hereda de Coordinate.
 * @author Alex
 * @date 18-6-2025
 *
 */

#ifndef COLOR_HPP
#define COLOR_HPP
#include "Coordinate.hpp"

/**
 * @class Color
 * @brief Representa un color RGB como una especialización de la clase Coordinate.
 *
 * La clase Color utiliza referencias a los miembros x, y, z de Coordinate para representar
 * los componentes rojo (r), verde (g) y azul (b) de un color, respectivamente.
 *
 * @note El componente w de Coordinate se establece en 0 para los colores.
 * @see Coordinate
 */
class Color: public Coordinate{
private:
public:
    double& r = x;
    double& g = y;
    double& b = z;

    Color(double r_, double g_, double b_): Coordinate(r_, g_, b_, 0){};
    Color() : Coordinate(0.0, 0.0, 0.0, 0.0){};
    Color(const Coordinate& c) : Color(c.x, c.y, c.z) {}
    Color(const Color& c) : Color(c.x, c.y, c.z) {}
    ~Color();    
    Color& operator=(const Color& c);
    friend std::ostream& operator<<(std::ostream& os, const Color &c);
    static Color fromRGB(double r_, double g_, double b_);
};

#endif /* COLOR_HPP */