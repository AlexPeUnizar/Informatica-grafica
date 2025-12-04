/**
 * @file Ray.hpp
 * @brief Declaracion de la clase Ray para representar un rayo en el espacio 3D.
 * 
 * Este archivo contiene la definicion de la clase Ray, que modela un rayo a partir de un punto de origen y una direccion.
 * Utilizado en aplicaciones de informática gráfica y trazado de rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef RAY_HPP
#define RAY_HPP
#include "Point.hpp"
#include "Vector.hpp"

/**
 * @class Ray
 * @brief Clase que representa un rayo en el espacio tridimensional.
 * 
 * Esta clase define un rayo mediante un punto de origen y una direccion, permitiendo calcular puntos a lo largo del rayo
 * y sobrecargar el operador de insercion para facilitar la impresion.
 */
class Ray{
private:
public:
    Point origin;
    Vector dir;
    Ray(const Point& origin, const Vector& dir);
    Ray(/* args */) = default;
    ~Ray();
    friend std::ostream& operator<<(std::ostream& os, const Ray &r);
    Point at(double t) const;
};

#endif /* RAY_HPP */