/**
 * @file Sphere.cpp
 * @brief Implementacion de la clase Sphere para la representacion y manejo de esferas en un sistema de gráficos por computadora.
 * 
 * Este archivo contiene la definicion de los metodos de la clase Sphere, que permite crear esferas, gestionar su interseccion con rayos y almacenar informacion relevante para el renderizado.
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
 * @brief Metodo que verifica si un rayo intersecta con la esfera.
 * 
 * Este metodo calcula la interseccion entre un rayo y la esfera, determinando si el rayo intersecta dentro de los limites especificados (tMin y tMax).
 * Si hay una interseccion, se llena la estructura de Intersection con los detalles de la interseccion.
 * 
 * @param ray Rayo que se está verificando para la interseccion.
 * @param tMin Valor minimo de t para considerar la interseccion.
 * @param tMax Valor máximo de t para considerar la interseccion.
 * @param intersection Estructura donde se almacenarán los detalles de la interseccion si ocurre.
 * @return bool Verdadero si hay una interseccion válida, falso en caso contrario.
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
    /*
    if(t0 < 0 && t1 < 0){
        return false;
    }
    
    intersection.t = (t0 > 0 && t1 > 0) ? std::min(t0, t1) : (t0 > 0 ? t0 : (t1 > 0 ? t1 : -1));
    intersection.intersectionPoint = ray.at(intersection.t);
    intersection.normal = normalize(intersection.intersectionPoint - this->origin);
    intersection.material = this->material;

    //std::cout << "t0: " << t0 << "; t1: " << t1 << std::endl;
    return (intersection.t >= tMin && intersection.t <= tMax);
    */
}

/**
 * @brief Aplica una transformacion matricial a la esfera.
 * 
 * Este metodo transforma la posicion del origen de la esfera utilizando la matriz de transformacion proporcionada.
 * Ademas, ajusta el radio de la esfera en funcion de las escalas aplicadas en cada eje.
 * 
 * @param m Matriz de transformacion a aplicar. 
 */
void Sphere::applyTransform(const Matrix& m) {
    origin = Point(m * origin);

    // Extraer escalas en cada eje
    double sx = module(Vector(m * Vector(1, 0, 0)));
    double sy = module(Vector(m * Vector(0, 1, 0)));
    double sz = module(Vector(m * Vector(0, 0, 1)));

    double scale = (sx + sy + sz) / 3.0;
    r *= scale;
}

