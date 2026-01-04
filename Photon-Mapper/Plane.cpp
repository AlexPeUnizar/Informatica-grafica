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
 * @brief Constructor de la clase Plane.
 * 
 * Crea un nuevo objeto Plane con la normal, distancia y material especificados.
 * 
 * @param normal Vector que representa la normal del plano.
 * @param dist   Distancia del plano al origen.
 * @param material Puntero compartido al material que se asignará al plano.
 */
Plane::Plane(const Vector& normal, const double dist, const std::shared_ptr<Material>& material): Figure(material){
    this->normal = normal;
    this->dist = dist;
}

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

/**
 * @brief Aplica una transformacion matricial al plano.
 * 
 * Este metodo transforma el plano utilizando la matriz de transformacion proporcionada.
 * La normal del plano se transforma usando el inverso transpuesto de la matriz,
 * y la distancia al origen se recalcula en base a un punto transformado en el plano.
 * 
 * @param m Matriz de transformacion a aplicar. 
 */
void Plane::applyTransform(const Matrix& m) {
    // Elegir un punto sobre el plano
    Point pointOnPlane = Point(normal * -dist); // punto p tal que n·p + d = 0

    // Transformar ese punto
    Point newPoint = m * pointOnPlane;

    // Transformar la normal usando el inverso transpuesto (solo válido si m es afín)
    Matrix inverseTransposed = transpose(inverse(m));
    Vector newNormal = normalize(Vector(inverseTransposed * normal));

    // Recalcular la nueva distancia al origen
    dist = -dotProduct(newNormal, newPoint);
    normal = newNormal;
}
