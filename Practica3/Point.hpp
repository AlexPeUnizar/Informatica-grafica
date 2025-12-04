/**
 * @file Point.hpp
 * @brief Declaracion de la clase Point para representar puntos en el espacio 3D.
 * 
 * Este archivo define la clase Point, que hereda de Coordinate y proporciona
 * operaciones y constructores especificos para puntos en el contexto de graficos
 * por computadora.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <cstdint>
#include "Vector.hpp"
#include "Coordinate.hpp"

/**
 * @class Point
 * @brief Clase que representa un punto en el espacio tridimensional.
 * 
 * Esta clase hereda de Coordinate y define un punto con coordenadas (x, y, z) y una componente homogenea w.
 * Proporciona operaciones para la resta de puntos, suma con escalares, impresion y multiplicacion con vectores.
 * 
 * @see Coordinate
 */
class Point: public Coordinate{
public:
    Point(double x, double y, double z) : Coordinate(x, y, z, 1.0){};
    Point(const Coordinate& c) : Coordinate(c.x, c.y, c.z, 1.0) {};
    ~Point();
    Point() = default;
    friend Vector operator-(Point const &p1, Point const &p2);
    friend Point operator+(double const s, Point const &p);
    friend Point operator+(Point const &p, double const s);
    friend std::ostream& operator<<(std::ostream& os, const Point &p);
    
    friend double operator*(const Point& p, const Vector &v);
    friend double operator*(const Vector &v, const Point& p);

};
#endif /* POINT_HPP */