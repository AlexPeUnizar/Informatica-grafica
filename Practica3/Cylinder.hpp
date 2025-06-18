/**
 * @file Cylinder.hpp
 * @brief Declaración de la clase Cylinder para representar un cilindro finito en el espacio 3D.
 * 
 * Este archivo contiene la definición de la clase Cylinder, que hereda de Figure y permite
 * modelar un cilindro mediante su base, eje, radio y altura, para aplicaciones de gráficos
 * por computadora y trazado de rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */

#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Figure.hpp"
#include "Point.hpp"

/** @brief Clase Cylinder que representa un cilindro en el espacio 3D.
 * 
 * Esta clase hereda de Figure y define un cilindro mediante su base, eje, radio y altura.
 * Implementa el método isIntersectedBy para determinar si un rayo intersecta con el cilindro.
 * @see Figure
 */
class Cylinder : public Figure {
private:
    Point baseCenter; // Centro de la base del cilindro
    Vector axis;      // Dirección del eje del cilindro (debe ser normalizada)
    double radius;    // Radio del cilindro
    double height;    // Altura del cilindro

public:
    Cylinder(const Point& baseCenter, const Vector& axis, double radius, double height, const std::shared_ptr<Material>& material)
        : Figure(material), baseCenter(baseCenter), axis(normalize(axis)), radius(radius), height(height) {}

    ~Cylinder() = default;

    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
};


#endif /* CYLINDER_HPP */