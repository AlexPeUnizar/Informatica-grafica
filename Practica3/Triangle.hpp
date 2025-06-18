/**
 * @file Triangle.hpp
 * @brief Declaración de la clase Triangle para representar un triángulo en el espacio 3D.
 * 
 * Esta clase hereda de Figure y define un triángulo mediante tres vértices.
 * Permite comprobar la intersección con un rayo y está diseñada para su uso en aplicaciones de gráficos por computadora.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Figure.hpp"
#include "Point.hpp"

/**
 * @class Triangle
 * @brief Clase que representa un triángulo en el espacio tridimensional.
 * 
 * Esta clase define un triángulo mediante tres vértices y permite verificar si un rayo intersecta con el triángulo.
 * La intersección se determina utilizando el método de Möller–Trumbore.
 * 
 * @see Figure
 */
class Triangle : public Figure {
private:
    Point v0, v1, v2; // Los tres vértices del triángulo

public:
    Triangle(const Point& v0, const Point& v1, const Point& v2, const std::shared_ptr<Material>& material)
        : Figure(material), v0(v0), v1(v1), v2(v2) {}
    virtual ~Triangle() = default;

    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
};

#endif /* TRIANGLE_HPP */