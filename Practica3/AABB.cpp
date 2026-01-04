/**
 * @file AABB.cpp
 * @author Alex
 * @brief Implementacion de la estructura AABB (Axis-Aligned Bounding Box) para gráficos 3D.
 * @date 2026-01-04
 * 
 */
#include "AABB.hpp"

/**
 * @brief Combina dos cajas delimitadoras alineadas a los ejes (AABB) en una sola que las englobe.
 * 
 * @param a La primera caja delimitadora AABB.
 * @param b La segunda caja delimitadora AABB.
 * @return AABB Una nueva caja delimitadora que contiene completamente a las dos cajas de entrada.
 * 
 * Este método calcula una nueva AABB que es lo suficientemente grande como para contener
 * completamente las dos AABB proporcionadas como entrada. Utiliza los valores mínimos y máximos
 * de las coordenadas de las cajas para determinar los límites de la nueva caja.
 */
AABB AABB::merge(const AABB& a, const AABB& b) {
    return AABB(
        Point(std::min(a.mn.x, b.mn.x), std::min(a.mn.y, b.mn.y), std::min(a.mn.z, b.mn.z)),
        Point(std::max(a.mx.x, b.mx.x), std::max(a.mx.y, b.mx.y), std::max(a.mx.z, b.mx.z))
    );
}

/**
 * @brief Verifica si un rayo intersecta con el Axis-Aligned Bounding Box (AABB).
 *
 * Este método utiliza el enfoque del "Slab method" para determinar si un rayo
 * intersecta con el AABB. Evalúa las intersecciones del rayo con los planos
 * delimitadores del AABB en cada uno de los tres ejes (x, y, z).
 *
 * @param r El rayo que se evalúa, representado por su origen y dirección.
 * @param tMin El límite inferior del rango de tiempo (t) para la intersección.
 * @param tMax El límite superior del rango de tiempo (t) para la intersección.
 * @return true Si el rayo intersecta con el AABB dentro del rango [tMin, tMax].
 * @return false Si no hay intersección o si la intersección está fuera del rango.
 */
bool AABB::hit(const Ray& r, double tMin, double tMax) const {
    // Slab method
    for (int axis = 0; axis < 3; ++axis) {
        double origin = (axis == 0) ? r.origin.x : (axis == 1) ? r.origin.y : r.origin.z;
        double dir    = (axis == 0) ? r.dir.x    : (axis == 1) ? r.dir.y    : r.dir.z;
        double minv   = (axis == 0) ? mn.x       : (axis == 1) ? mn.y       : mn.z;
        double maxv   = (axis == 0) ? mx.x       : (axis == 1) ? mx.y       : mx.z;

        double invD = 1.0 / dir;
        double t0 = (minv - origin) * invD;
        double t1 = (maxv - origin) * invD;
        if (invD < 0.0) std::swap(t0, t1);

        tMin = std::max(tMin, t0);
        tMax = std::min(tMax, t1);
        if (tMax <= tMin) return false;
    }
    return true;
}