#include "Triangle.hpp"
#include "Vector.hpp"

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
