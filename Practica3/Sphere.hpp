/**
 * @file Sphere.hpp
 * @brief Declaración de la clase Sphere para la representación de esferas en gráficos por computadora.
 * 
 * Esta clase hereda de Figure y permite definir esferas en el espacio 3D, especificando su origen, radio y material.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Figure.hpp"
#include "Point.hpp"

/**
 * @class Sphere
 * @brief Clase que representa una esfera en el espacio tridimensional.
 * 
 * Esta clase define una esfera mediante un punto de origen, un radio y un material asociado.
 * Permite verificar si un rayo intersecta con la esfera y proporciona información sobre la intersección.
 * 
 * @see Figure
 */
class Sphere : public Figure{
private:
    Point origin;
    double r;
public:
    Sphere(const Point &origin, double r, const std::shared_ptr<Material>& material);
    Sphere(double x, double y, double z, double r, const std::shared_ptr<Material>& material): Figure(material), origin(Point(x, y, z)), r(r){};
    ~Sphere();
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
};

#endif /* SPHERE_HPP */