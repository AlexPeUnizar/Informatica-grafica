/**
 * @file Plane.cpp
 * @brief Implementacion de la clase Plane para representar planos en el espacio 3D.
 * 
 * Este archivo contiene la definicion de los metodos de la clase Plane, que permite
 * modelar planos y calcular intersecciones con rayos, util en aplicaciones de gráficos
 * por computadora y trazado de rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Plane.hpp"

/**
 * @brief Destructor de la clase Plane.
 * Este destructor libera los recursos asociados con el vector normal del plano.
 */
Plane::~Plane(){
    this->normal.~Vector();
}

/**
 * @brief Constructor de la clase Plane.
 * 
 * Inicializa un plano con un vector normal, una distancia desde el origen y un material asociado.
 * 
 * @param normal Vector que representa la normal del plano.
 * @param dist Distancia desde el origen al plano.
 * @param material Material asociado al plano.
 */
Plane::Plane(const Vector& normal, const double dist, const std::shared_ptr<Material>& material): Figure(material){
    this->normal = normal;
    this->dist = dist;
}
/*
Plane::Plane(const Point& p1, const Point& p2, const Point& p3){
    this->normal = normalize(crossProduct((p1-p2), (p3-p2)));
}
Plane::Plane(const Vector& t1, const Vector& t2){
    
}
Plane::Plane(const Vector& normal){
    
}
*/

/**
 * @brief Metodo que verifica si un rayo intersecta con el plano.
 * 
 * Este metodo calcula la interseccion entre un rayo y el plano, determinando si el rayo
 * intersecta dentro de los limites especificados (tMin y tMax). Si hay una interseccion,
 * se llena la estructura de Intersection con los detalles de la interseccion.
 * 
 * @param ray Rayo que se está verificando para la interseccion.
 * @param tMin Valor minimo de t para considerar la interseccion.
 * @param tMax Valor máximo de t para considerar la interseccion.
 * @param intersection Estructura donde se almacenarán los detalles de la interseccion si ocurre.
 * @return bool Verdadero si hay una interseccion válida, falso en caso contrario.
 */
bool Plane::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const{
    if(!this->visible){
        return false;
    }

    double denom = dotProduct(ray.dir, this->normal);
    if(denom == 0){
        return false;
    }
    double div = this->dist + (ray.origin * (this->normal));
    
    intersection.t = -(div/denom);
    intersection.normal = this->normal;
    intersection.intersectionPoint = ray.at(intersection.t);
    intersection.material = this->material;
    intersection.figureName = typeid(this).name();


    return (intersection.t >= 0 && intersection.t > tMin && intersection.t < tMax);
}


           