/**
 * @file Vector.hpp
 * @brief Declaración de la clase Vector para operaciones en el espacio 3D.
 * 
 * Esta clase extiende la funcionalidad de la clase Coordinate para representar y manipular vectores en tres dimensiones,
 * proporcionando operadores y funciones amigas para operaciones vectoriales comunes como suma, resta, producto cruzado,
 * producto escalar, normalización, reflexión y refracción.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <stdint.h>
#include "Coordinate.hpp"

/**
 * @class Vector
 * @brief Clase que representa un vector en el espacio tridimensional.
 * 
 * Esta clase hereda de Coordinate y proporciona operaciones vectoriales como suma, resta, producto cruzado,
 * producto escalar, normalización, reflexión y refracción. También permite la impresión del vector en un formato legible.
 */
class Vector: public Coordinate{
private:

public:
    Vector(double _x, double _y, double _z) : Coordinate(_x, _y, _z, 0.0){};
    Vector(const Coordinate& c) : Coordinate(c.x, c.y, c.z, 0.0) {};

    ~Vector() = default;
    Vector() = default;
    friend std::ostream& operator<<(std::ostream& os, const Vector &v);
    friend Vector operator+(const Vector &v1, const Vector &v2);
    friend Vector operator-(const Vector &v1, const Vector &v2);
    friend Vector crossProduct(const Vector &v1, const Vector &v2);
    friend double dotProduct(const Vector &v1, const Vector &v2);
    friend Vector operator*(const Vector &v, const double s);
    friend Vector operator*(const double s, const Vector &v);
    friend Vector operator/(const Vector &v, const double s);
    friend double module(const Vector &v);
    friend double angle(const Vector &v1, const Vector &v2);
    friend Vector normalize(const Vector &v);
    friend Vector reflect(const Vector& incident, const Vector& normal);
    friend Vector refract(const Vector& incident, const Vector& normal, double ior_ratio);
    friend Vector operator-(const Vector& v);
};


#endif /* VECTOR_HPP */