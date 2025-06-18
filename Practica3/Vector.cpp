/**
 * @file Vector.cpp
 * @brief Implementación de operaciones y utilidades para la clase Vector en 3D.
 * 
 * Este archivo contiene la definición de operadores y funciones auxiliares para el manejo de vectores tridimensionales,
 * incluyendo suma, resta, producto escalar, producto vectorial, normalización, reflexión y refracción, entre otros.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Vector.hpp"
#include <math.h>

/** 
 * @brief Sobrecarga del operador de inserción para imprimir un vector.
 * 
 * Este operador permite imprimir un vector en un formato legible, mostrando sus componentes x, y, z.
 * 
 * @param os Flujo de salida donde se imprimirá el vector.
 * @param v Vector a imprimir.
 * @return std::ostream& Flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const Vector &v){
    os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

/**
 * @brief Sobrecarga del operador de suma para sumar dos vectores.
 * 
 * Este operador permite sumar dos vectores componente a componente.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return Vector Resultado de la suma de v1 y v2.
 */
Vector operator+(const Vector &v1, const Vector &v2){
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

/**
 * @brief Sobrecarga del operador de resta para restar dos vectores.
 * 
 * Este operador permite restar dos vectores componente a componente.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return Vector Resultado de la resta de v1 y v2.
 */
Vector operator-(const Vector &v1, const Vector &v2){
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/**
 * @brief Calcula el producto cruzado de dos vectores.
 * 
 * Esta función calcula el producto cruzado entre dos vectores tridimensionales,
 * devolviendo un nuevo vector perpendicular a ambos.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return Vector Resultado del producto cruzado de v1 y v2.
 */
Vector crossProduct(const Vector &v1, const Vector &v2){
    return Vector((v1.y * v2.z - v1.z * v2.y),
                      (v1.z * v2.x - v1.x * v2.z),
                      (v1.x * v2.y - v1.y * v2.x));
}

/**
 * @brief Calcula el producto escalar de dos vectores.
 * 
 * Esta función calcula el producto escalar entre dos vectores tridimensionales,
 * devolviendo un valor escalar que representa la magnitud del coseno del ángulo entre ellos.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return double Resultado del producto escalar de v1 y v2.
 */
double dotProduct(const Vector &v1, const Vector &v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/**
 * @brief Sobrecarga del operador de multiplicación para escalar un vector.
 * 
 * Este operador permite multiplicar un vector por un escalar, escalando sus componentes.
 * 
 * @param v Vector a escalar.
 * @param s Escalar por el cual se multiplica el vector.
 * @return Vector Resultado de la multiplicación del vector por el escalar.
 */
Vector operator*(const Vector &v, const double s){
    return Vector(v.x * s, v.y * s, v.z * s);
}

/**
 * @brief Sobrecarga del operador de multiplicación para escalar un vector.
 * 
 * Este operador permite multiplicar un escalar por un vector, escalando sus componentes.
 * 
 * @param s Escalar por el cual se multiplica el vector.
 * @param v Vector a escalar.
 * @return Vector Resultado de la multiplicación del escalar por el vector.
 */
Vector operator*(const double s, const Vector &v){
    return v*s;
}

/**
 * @brief Sobrecarga del operador de división para escalar un vector.
 * 
 * Este operador permite dividir un vector por un escalar, escalando sus componentes.
 * 
 * @param v Vector a dividir.
 * @param s Escalar por el cual se divide el vector.
 * @return Vector Resultado de la división del vector por el escalar.
 */
Vector operator/(const Vector &v, const double s){
    return Vector(v.x / s, v.y / s, v.z / s);
}

/**
 * @brief Calcula la magnitud (módulo) de un vector.
 * 
 * Esta función calcula la magnitud del vector utilizando la fórmula de la raíz cuadrada de la suma de los cuadrados
 * de sus componentes.
 * 
 * @param v Vector del cual se desea calcular la magnitud.
 * @return double Magnitud del vector v.
 */
double module(const Vector &v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

/**
 * @brief Calcula el ángulo entre dos vectores.
 * 
 * Esta función calcula el ángulo en radianes entre dos vectores utilizando el producto escalar y las magnitudes de los vectores.
 * 
 * @param v1 Primer vector.
 * @param v2 Segundo vector.
 * @return double Ángulo en radianes entre v1 y v2.
 */
double angle(const Vector &v1, const Vector &v2){
    return acos((dotProduct(v1,v2))/(module(v1)*module(v2)));
}

/**
 * @brief Normaliza un vector, convirtiéndolo en un vector unitario.
 * 
 * Esta función divide cada componente del vector por su magnitud, devolviendo un vector con una magnitud de 1.
 * 
 * @param v Vector a normalizar.
 * @return Vector Vector normalizado.
 */
Vector normalize(const Vector &v){
    return v/module(v);
}

/**
 * @brief Refleja un vector incidente respecto a una normal.
 * 
 * Esta función calcula el vector reflejado de un vector incidente dado una normal,
 * utilizando la fórmula de reflexión.
 * 
 * @param incident Vector incidente.
 * @param normal Normal respecto a la cual se refleja el vector incidente.
 * @return Vector Vector reflejado.
 */
Vector reflect(const Vector& incident, const Vector& normal) {
    return incident - 2.0f * dotProduct(incident, normal) * normal;
}

/**
 * @brief Refracta un vector incidente respecto a una normal y un índice de refracción.
 * 
 * Esta función calcula el vector refractado de un vector incidente dado una normal y un índice de refracción,
 * utilizando la ley de Snell.
 * 
 * @param incident Vector incidente.
 * @param normal Normal respecto a la cual se refracta el vector incidente.
 * @param ior_ratio Índice de refracción del medio al que se está refractando.
 * @return Vector Vector refractado, o un vector nulo si ocurre reflexión total interna.
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
 * @brief Sobrecarga del operador de negación para invertir un vector.
 * 
 * Este operador permite invertir las componentes de un vector, devolviendo un nuevo vector con los signos opuestos.
 * 
 * @param v Vector a invertir.
 * @return Vector Vector invertido.
 */
Vector operator-(const Vector& v){
    return Vector(-v.x, -v.y, -v.z);
}
