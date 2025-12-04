/**
 * @file Triangle.cpp
 * @brief Implementacion de la clase Triangle y su metodo de interseccion con un rayo.
 * 
 * Este archivo contiene la logica para determinar si un rayo intersecta un triángulo en el espacio 3D,
 * utilizando el algoritmo de Möller-Trumbore. Se calcula la interseccion y, en caso afirmativo, se almacena
 * la informacion relevante en la estructura Intersection.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Triangle.hpp"
#include "Vector.hpp"

/**
 * @brief Comprueba si un rayo intersecta con el triángulo.
 * 
 * Este metodo utiliza el algoritmo de Möller-Trumbore para determinar si un rayo intersecta con el triángulo definido por sus vertices.
 * Si hay una interseccion, se rellena la informacion en el objeto `intersection`.
 * 
 * @param ray El rayo que se está comprobando para la interseccion.
 * @param tMin El valor minimo de t para considerar una interseccion válida.
 * @param tMax El valor máximo de t para considerar una interseccion válida.
 * @param intersection Referencia al objeto Intersection donde se almacenará la informacion de la interseccion si ocurre.
 * @return true Si hay una interseccion válida.
 * @return false Si no hay interseccion o si el rayo es paralelo al triángulo.
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

    // Vector desde el vertice v0 hasta el origen del rayo
    Vector s = ray.origin - v0;

    // Calcula la coordenada baricentrica u
    double u = dotProduct(s, h) * invDet;
    if (u < 0.0 || u > 1.0) return false;

    // Calcula la coordenada baricentrica v
    Vector q = crossProduct(s, edge1);
    double v = dotProduct(ray.dir, q) * invDet;
    if (v < 0.0 || u + v > 1.0) return false;

    // Calcula t para determinar el punto de interseccion
    double t = dotProduct(edge2, q) * invDet;
    if (t < tMin || t > tMax) return false;

    // Si hay interseccion, rellena la informacion en el objeto `intersection`
    intersection.t = t;
    intersection.intersectionPoint = ray.at(t);
    intersection.normal = normalize(crossProduct(edge1, edge2));
    intersection.material = this->material;
    intersection.figureName = "Triangle";

    return true;
}
