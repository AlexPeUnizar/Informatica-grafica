/**
 * @file Direction.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <stdint.h>
#include "Coordinate.hpp"

class Vector: public Coordinate{
private:

public:
    Vector(double x, double y, double z) : Coordinate(x, y, z, 0.0){};
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