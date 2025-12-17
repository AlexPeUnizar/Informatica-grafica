#include "Triangle.hpp"
#include "Vector.hpp"

bool Triangle::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const {
    if(!this->visible) return false;

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

    intersection.b1 = u;
    intersection.b2 = v;
    intersection.b0 = 1.0 - u - v;

    Vector faceN = normalize(crossProduct(edge1, edge2));

    if (hasVertexNormals) {
        Vector smoothN = (intersection.b0 * n0) + (intersection.b1 * n1) + (intersection.b2 * n2);
        intersection.normal = normalize(smoothN);
    } else {
        intersection.normal = faceN;
    }

    if (dotProduct(intersection.normal, ray.dir) > 0.0) {
        intersection.normal = -intersection.normal;
    }

    intersection.material = this->material;
    intersection.figureName = "Triangle";

    return true;
}


void Triangle::applyTransform(const Matrix& m) {
    v0 = m * v0;
    v1 = m * v1;
    v2 = m * v2;

    if (hasVertexNormals) {
        n0 = normalize((Vector)(m * n0));
        n1 = normalize((Vector)(m * n1));
        n2 = normalize((Vector)(m * n2));
    }
}
