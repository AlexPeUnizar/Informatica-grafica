/**
 * @file Sphere.cpp
 * @brief Implementación de la clase Sphere para la representación y manejo de esferas en un sistema de gráficos por computadora.
 * 
 * Este archivo contiene la definición de los métodos de la clase Sphere, que permite crear esferas, gestionar su intersección con rayos y almacenar información relevante para el renderizado.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Sphere.hpp"
#include <math.h>

/**
 * @brief Constructor de la clase Sphere.
 * 
 * Este constructor inicializa una esfera con un punto de origen, un radio y un material asociado.
 * 
 * @param origin Punto de origen de la esfera.
 * @param r Radio de la esfera.
 * @param material Material asociado a la esfera.
 */
Sphere::Sphere(const Point &origin, double r, const std::shared_ptr<Material>& material): Figure(material){
    this->origin = origin;
    this->r = r;
}
/**
 * @brief Destructor de la clase Sphere.
 * 
 * Este destructor libera los recursos asociados con el punto de origen de la esfera.
 */
Sphere::~Sphere(){
    origin.~Point();
}

/**
 * @brief Método que verifica si un rayo intersecta con la esfera.
 * 
 * Este método calcula la intersección entre un rayo y la esfera, determinando si el rayo intersecta dentro de los límites especificados (tMin y tMax).
 * Si hay una intersección, se llena la estructura de Intersection con los detalles de la intersección.
 * 
 * @param ray Rayo que se está verificando para la intersección.
 * @param tMin Valor mínimo de t para considerar la intersección.
 * @param tMax Valor máximo de t para considerar la intersección.
 * @param intersection Estructura donde se almacenarán los detalles de la intersección si ocurre.
 * @return bool Verdadero si hay una intersección válida, falso en caso contrario.
 */
bool Sphere::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const{
    if(!this->visible){
        return false;
    }
    Vector vectorToCenter = ray.origin - this->origin;
    double a = dotProduct(ray.dir, ray.dir);
    double b = 2 * dotProduct(vectorToCenter, ray.dir);
    double c = dotProduct(vectorToCenter, vectorToCenter) - this->r * this->r;
    //std::cout << "a: " << a << "; b: " << b << "; c: " << c << std::endl;
    double delta = b*b - 4 * a * c;
    //std::cout << "delta: " << delta << std::endl;

    if(delta < 0){
        return false;
    }
    
    double t0 = (-b - sqrt(delta)) / (2 * a);
    if(t0 < tMax && t0 > tMin){
        intersection.t = t0;
        intersection.intersectionPoint = ray.at(intersection.t);
        intersection.normal = normalize(intersection.intersectionPoint - this->origin);
        intersection.material = this->material;
        intersection.figureName = "Sphere";
        return true;
    }
    
    double t1 = (-b + sqrt(delta)) / (2 * a);
    if(t1 < tMax && t1 > tMin){
        intersection.t = t1;
        intersection.intersectionPoint = ray.at(intersection.t);
        intersection.normal = normalize(intersection.intersectionPoint - this->origin);
        intersection.material = this->material;
        intersection.figureName = typeid(this).name();
        return true;
    }
    return false;
}
