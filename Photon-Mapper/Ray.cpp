/**
 * @file Ray.cpp
 * @brief Implementacion de la clase Ray para la gestion de rayos en gráficos por computadora.
 * 
 * Este archivo contiene la implementacion de los metodos de la clase Ray, que representa un rayo definido por un punto de origen y una direccion en el espacio tridimensional.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Ray.hpp"

/**
 * @brief Constructor de la clase Ray.
 * 
 * Inicializa un rayo con un punto de origen y una direccion normalizada.
 * 
 * @param origin Punto de origen del rayo.
 * @param dir Direccion del rayo, que será normalizada.
 */
Ray::Ray(const Point& origin, const Vector& dir){
    this->origin = origin;
    this->dir = normalize(dir);
}

/**
 * @brief Sobrecarga del operador de insercion para imprimir un rayo.
 * 
 * Este operador permite imprimir un rayo en un formato legible, mostrando su origen y direccion.
 * 
 * @param os Flujo de salida donde se imprimirá el rayo.
 * @param r Rayo a imprimir.
 * @return std::ostream& Flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const Ray &r){
    os << "Ray(" << "Origin: " << r.origin << "; Direcction: " << r.dir << ")";
    return os;
}

/**
 * @brief Metodo que calcula un punto a lo largo del rayo en una distancia t.
 * 
 * Este metodo devuelve un punto en el rayo a una distancia t desde el origen, siguiendo la direccion del rayo.
 * 
 * @param t Distancia desde el origen del rayo.
 * @return Point Punto en el rayo a la distancia t.
 */
Point Ray::at(double t) const{
    return Point(
        this->origin.x + t*this->dir.x,
        this->origin.y + t*this->dir.y,
        this->origin.z + t*this->dir.z
    );
}

