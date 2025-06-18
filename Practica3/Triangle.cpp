/**
 * @file Triangle.cpp
 * @brief Implementación de la clase Triangle y su método de intersección con un rayo.
 * 
 * Este archivo contiene la lógica para determinar si un rayo intersecta un triángulo en el espacio 3D,
 * utilizando el algoritmo de Möller-Trumbore. Se calcula la intersección y, en caso afirmativo, se almacena
 * la información relevante en la estructura Intersection.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Triangle.hpp"
#include "Vector.hpp"

/**
 * @brief Comprueba si un rayo intersecta con el triángulo.
 * 
 * Este método utiliza el algoritmo de Möller-Trumbore para determinar si un rayo intersecta con el triángulo definido por sus vértices.
 * Si hay una intersección, se rellena la información en el objeto `intersection`.
 * 
 * @param ray El rayo que se está comprobando para la intersección.
 * @param tMin El valor mínimo de t para considerar una intersección válida.
 * @param tMax El valor máximo de t para considerar una intersección válida.
 * @param intersection Referencia al objeto Intersection donde se almacenará la información de la intersección si ocurre.
 * @return true Si hay una intersección válida.
 * @return false Si no hay intersección o si el rayo es paralelo al triángulo.
 */
bool Triangle::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const {
    // Calcula los bordes del triángulo
    Vector edge1 = v1 - v0;
    Vector edge2 = v2 - v0;

    // Calcula el determinante con el producto cruzado
    Vector h = crossProduct(ray.dir, edge2);
    double det = dotProduct(edge1, h);

    // Si el determinante es pequeño, el rayo es paralelo al triángulo
    if (std::abs(det) < 1e-6) return false;

    double invDet = 1.0 / det;

    // Vector desde el vértice v0 hasta el origen del rayo
    Vector s = ray.origin - v0;

    // Calcula la coordenada baricéntrica u
    double u = dotProduct(s, h) * invDet;
    if (u < 0.0 || u > 1.0) return false;

    // Calcula la coordenada baricéntrica v
    Vector q = crossProduct(s, edge1);
    double v = dotProduct(ray.dir, q) * invDet;
    if (v < 0.0 || u + v > 1.0) return false;

    // Calcula t para determinar el punto de intersección
    double t = dotProduct(edge2, q) * invDet;
    if (t < tMin || t > tMax) return false;

    // Si hay intersección, rellena la información en el objeto `intersection`
    intersection.t = t;
    intersection.intersectionPoint = ray.at(t);
    intersection.normal = normalize(crossProduct(edge1, edge2));
    intersection.material = this->material;
    intersection.figureName = "Triangle";

    return true;
}
