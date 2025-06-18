/**
 * @file Cylinder.cpp
 * @brief Implementación de la clase Cylinder para la detección de intersecciones con rayos en un cilindro.
 * 
 * Este archivo contiene la lógica para calcular la intersección de un rayo con un cilindro, incluyendo tanto el cuerpo como las tapas del cilindro.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Cylinder.hpp"
#include <math.h>

/**
 * @brief Verifica si un rayo intersecta con el cilindro.
 * 
 * Este método calcula la intersección de un rayo con el cilindro, considerando tanto el cuerpo del cilindro como sus tapas.
 * Si hay una intersección, se actualiza el objeto Intersection con los detalles de la intersección.
 * 
 * @param ray El rayo a verificar para la intersección.
 * @param tMin El valor mínimo de t para considerar la intersección.
 * @param tMax El valor máximo de t para considerar la intersección.
 * @param intersection Objeto Intersection donde se almacenarán los detalles de la intersección si ocurre.
 * @return true Si el rayo intersecta con el cilindro, false en caso contrario.
 */
bool Cylinder::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const {
    // Vector hacia la base del cilindro
    Vector delta = ray.origin - baseCenter;

    // Direcciones ortogonales a la proyección en el eje del cilindro
    Vector w = ray.dir - axis * dotProduct(ray.dir, axis);
    Vector deltaW = delta - axis * dotProduct(delta, axis);

    // Cálculo para intersección con el cuerpo del cilindro
    double a = dotProduct(w, w);
    double b = 2 * dotProduct(w, deltaW);
    double c = dotProduct(deltaW, deltaW) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        // Soluciones cuadráticas
        double t0 = (-b - sqrt(discriminant)) / (2 * a);
        double t1 = (-b + sqrt(discriminant)) / (2 * a);

        // Verifica rango de altura del cilindro para el cuerpo
        for (double t : {t0, t1}) {
            if (t > tMin && t < tMax) {
                Point pCuerpo = ray.at(t);
                double hCuerpo = dotProduct(pCuerpo - baseCenter, axis);

                if (hCuerpo >= 0 && hCuerpo <= height) {
                    intersection.t = t;
                    intersection.intersectionPoint = pCuerpo;
                    Vector outwardNormal = normalize(pCuerpo - (Point)((Coordinate)baseCenter + (Coordinate)(axis * hCuerpo)));
                    intersection.normal = dotProduct(outwardNormal, ray.dir) < 0 ? outwardNormal : -outwardNormal;
                    intersection.material = this->material;
                    intersection.figureName = "Cylinder";
                    return true;
                }
            }
        }
    }

    // Cálculo para intersección con las tapas
    for (int i = 0; i < 2; i++) {
        double hTapa = (i == 0) ? 0 : height;
        Point centerTapa = (Point)((Coordinate)baseCenter + (Coordinate)(axis * hTapa));

        double tTapa = dotProduct(centerTapa - ray.origin, axis) / dotProduct(ray.dir, axis);
        if (tTapa > tMin && tTapa < tMax) {
            Point pTapa = ray.at(tTapa);
            if (module(pTapa - centerTapa) <= radius) {
                intersection.t = tTapa;
                intersection.intersectionPoint = pTapa;
                intersection.normal = (i == 0) ? -axis : axis;
                intersection.material = this->material;
                intersection.figureName = "Cylinder";
                return true;
            }
        }
    }

    return false;
}