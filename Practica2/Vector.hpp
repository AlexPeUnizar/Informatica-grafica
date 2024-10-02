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
    ~Vector();
    Vector();
    friend std::ostream& operator<<(std::ostream& os, const Vector &v);
    friend std::shared_ptr<Vector> operator+(const Vector &v1, const Vector &v2);
    friend std::shared_ptr<Vector> operator-(const Vector &v1, const Vector &v2);
    friend std::shared_ptr<Vector> crossProduct(const Vector &v1, const Vector &v2);
    friend int32_t dotProduct(const Vector &v1, const Vector &v2);
    friend std::shared_ptr<Vector> operator*(const Vector &v, const int32_t s);
    friend std::shared_ptr<Vector> operator*(const int32_t s, const Vector &v);
    friend std::shared_ptr<Vector> operator/(const Vector &v, const double s);
    friend double module(const Vector &v);
    friend double angle(const Vector &v1, const Vector &v2);
    friend std::shared_ptr<Vector> normalize(const Vector &v);

};


#endif /* VECTOR_HPP */