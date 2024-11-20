/**
 * @file Point.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
#include <cstdint>
#include "Vector.hpp"
#include "Coordinate.hpp"

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