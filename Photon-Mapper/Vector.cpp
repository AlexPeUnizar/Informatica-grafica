/**
 * @file Vector.cpp
 * @brief Implementacion de operaciones y utilidades para la clase Vector en 3D.
 * 
 * Este archivo contiene la definicion de operadores y funciones auxiliares para el manejo de vectores tridimensionales,
 * incluyendo suma, resta, producto escalar, producto vectorial, normalizacion, reflexion y refraccion, entre otros.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Vector.hpp"
#include <math.h>
#include "Utils.hpp"

/**
 * @brief Operador de salida sobrecargado para la clase Vector.
 * 
 * Esta funcion permite imprimir el objeto Vector en un formato legible.
 * 
 * @param os Flujo de salida donde escribir.
 * @param v Objeto Vector que se va a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Vector &v){
    os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

/**
 * @brief Suma dos vectores tridimensionales.
 * 
 * Esta funcion realiza la suma componente a componente de dos vectores 3D.
 * 
 * @param v1 Primer vector a sumar.
 * @param v2 Segundo vector a sumar.
 * @return Vector Resultado de la suma de los dos vectores.
 */
Vector operator+(const Vector &v1, const Vector &v2){
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

/**
 * @brief Resta dos vectores tridimensionales.
 * 
 * Esta funcion realiza la resta componente a componente de dos vectores 3D.
 * 
 * @param v1 Vector del cual se resta.
 * @param v2 Vector que se resta.
 * @return Vector Resultado de la resta de los dos vectores.
 */
Vector operator-(const Vector &v1, const Vector &v2){
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/**
 * @brief Calcula el producto cruzado de dos vectores tridimensionales.
 * 
 * Esta funcion calcula el producto cruzado entre dos vectores 3D, resultando en un nuevo vector perpendicular a ambos.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return Vector Resultado del producto cruzado.
 */
Vector crossProduct(const Vector &v1, const Vector &v2){
    return Vector((v1.y * v2.z - v1.z * v2.y),
                      (v1.z * v2.x - v1.x * v2.z),
                      (v1.x * v2.y - v1.y * v2.x));
}

/**
 * @brief Calcula el producto escalar de dos vectores tridimensionales.
 * 
 * Esta funcion calcula el producto escalar entre dos vectores 3D, resultando en un valor escalar.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return double Resultado del producto escalar.
 */
double dotProduct(const Vector &v1, const Vector &v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/**
 * @brief Multiplica un vector tridimensional por un escalar.
 * 
 * Esta funcion escala un vector 3D multiplicando cada una de sus componentes por un valor escalar.
 * 
 * @param v Vector a escalar.
 * @param s Escalar por el cual se multiplica el vector.
 * @return Vector Resultado del vector escalado.
 */
Vector operator*(const Vector &v, const double s){
    return Vector(v.x * s, v.y * s, v.z * s);
}

/**
 * @brief Multiplica un escalar por un vector tridimensional.
 * 
 * Esta funcion escala un vector 3D multiplicando cada una de sus componentes por un valor escalar.
 * 
 * @param s Escalar por el cual se multiplica el vector.
 * @param v Vector a escalar.
 * @return Vector Resultado del vector escalado.
 */
Vector operator*(const double s, const Vector &v){
    return v*s;
}

/**
 * @brief Divide un vector tridimensional por un escalar.
 * 
 * Esta funcion escala un vector 3D dividiendo cada una de sus componentes por un valor escalar.
 * 
 * @param v Vector a escalar.
 * @param s Escalar por el cual se divide el vector.
 * @return Vector Resultado del vector escalado.
 */
Vector operator/(const Vector &v, const double s){
    return Vector(v.x / s, v.y / s, v.z / s);
}

/**
 * @brief Calcula el modulo (magnitud) de un vector tridimensional.
 * 
 * Esta funcion calcula la magnitud de un vector 3D utilizando la formula de la raiz cuadrada de la suma de los cuadrados de sus componentes.
 * 
 * @param v Vector del cual se calcula el modulo.
 * @return double Modulo del vector.
 */
double module(const Vector &v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

/**
 * @brief Calcula el angulo entre dos vectores tridimensionales.
 * 
 * Esta funcion calcula el angulo en radianes entre dos vectores 3D utilizando el producto escalar y las magnitudes de los vectores.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return double Angulo entre los dos vectores en radianes.
 */
double angle(const Vector &v1, const Vector &v2){
    return acos((dotProduct(v1,v2))/(module(v1)*module(v2)));
}

/**
 * @brief Normaliza un vector tridimensional.
 * 
 * Esta funcion devuelve un nuevo vector que tiene la misma direccion que el vector original pero con una magnitud de 1.
 * 
 * @param v Vector a normalizar.
 * @return Vector Vector normalizado.
 */
Vector normalize(const Vector &v){
    return v/module(v);
}

/**
 * @brief Calcula la reflexion de un vector incidente sobre una normal.
 * 
 * Esta funcion calcula el vector reflejado dado un vector incidente y una normal utilizando la formula de reflexion.
 * 
 * @param incident Vector incidente.
 * @param normal Normal sobre la cual se refleja el vector.
 * @return Vector Vector reflejado.
 */
Vector reflect(const Vector& incident, const Vector& normal) {
    return incident - 2.0f * dotProduct(incident, normal) * normal;
}

/**
 * @brief Calcula la refraccion de un vector incidente a traves de una superficie con una normal dada.
 * 
 * Esta funcion calcula el vector refractado utilizando la ley de Snell, dado un vector incidente,
 * una normal y la relacion de indices de refraccion.
 * 
 * @param incident Vector incidente.
 * @param normal Normal de la superficie.
 * @param ior_ratio Relacion de indices de refraccion (n1/n2).
 * @return Vector Vector refractado.
 */
Vector refract(const Vector& incident, const Vector& normal, double ior_ratio) {
    Vector incidentNorm = normalize(incident);
    Vector normalNorm = normalize(normal);

    double cosi = dotProduct(incidentNorm, normalNorm);
    if (cosi < -1.0) cosi = -1.0;
    if (cosi > 1.0) cosi = 1.0;

    double etai = 1.0;
    double etat = ior_ratio;
    if (cosi > 0) {
        normalNorm = -normalNorm;
        std::swap(etai, etat);
    }

    double eta = etai / etat;
    double k = 1.0 - eta * eta * (1.0 - cosi * cosi);

    if (k < 0.0) {
        return Vector(0, 0, 0);  // Reflexión total interna
    }

    return eta * incidentNorm + (eta * cosi - sqrt(k)) * normalNorm;
}

/**
 * @brief Operador de negacion para la clase Vector.
 * 
 * Esta funcion devuelve un nuevo vector que es el opuesto del vector original.
 * 
 * @param v Vector a negar.
 * @return Vector Vector negado.
 */
Vector operator-(const Vector& v){
    return Vector(-v.x, -v.y, -v.z);
}

