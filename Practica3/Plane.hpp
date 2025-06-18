/**
 * @file Plane.hpp
 * @brief Declaración de la clase Plane para la representación de planos en el sistema de gráficos.
 * 
 * Esta clase define la estructura y las operaciones básicas para trabajar con planos en el contexto de gráficos computacionales.
 * Hereda de la clase Figure e incluye métodos para la intersección con rayos y la gestión de materiales asociados.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef PLANE_HPP
#define PLANE_HPP
#include "Figure.hpp"
#include "Vector.hpp"
#include "Point.hpp"

/**
 * @class Plane
 * @brief Clase que representa un plano en el espacio tridimensional.
 * 
 * Esta clase define un plano mediante un vector normal y una distancia desde el origen.
 * Permite verificar si un rayo intersecta con el plano y proporciona información sobre la intersección.
 * 
 * @see Figure
 */
class Plane: public Figure{
private:
    Vector normal;
    double dist;

public:
    Plane(const Vector& normal, const double dist, const std::shared_ptr<Material>& material);
    /*
    Plane(const Point& p1, const Point& p2, const Point& p3);
    Plane(const Vector& t1, const Vector& t2);
    Plane(const Vector& normal);
    */
    Plane() = default;
    ~Plane();
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
};

#endif /* PLANE_HPP */