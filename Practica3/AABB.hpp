/**
 * @file AABB.hpp
 * @author Alex
 * @brief Declaracion de la estructura AABB (Axis-Aligned Bounding Box) para gráficos 3D.
 * @date 2026-01-04
 * 
 */
#ifndef AABB_HPP
#define AABB_HPP

#include "Point.hpp"
#include "Ray.hpp"
#include <algorithm>
#include <limits>

/**
 * @brief Estructura AABB que representa una caja delimitadora alineada a los ejes.
 * 
 * Esta estructura almacena los puntos mínimo (mn) y máximo (mx) que definen la caja delimitadora.
 * Proporciona métodos para combinar dos AABB y para verificar la intersección con un rayo.
 */
struct AABB {
    Point mn;
    Point mx;

    AABB()
        : mn(Point( std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity())),
          mx(Point(-std::numeric_limits<double>::infinity(),
                   -std::numeric_limits<double>::infinity(),
                   -std::numeric_limits<double>::infinity())) {}

    AABB(const Point& a, const Point& b) : mn(a), mx(b) {}

    static AABB merge(const AABB& a, const AABB& b);

    bool hit(const Ray& r, double tMin, double tMax) const;
};

#endif
