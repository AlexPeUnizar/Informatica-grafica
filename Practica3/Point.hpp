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
    ~Point();
    Point() = default;
    friend std::shared_ptr<Vector> operator-(Point const &p1, Point const &p2);
    friend std::shared_ptr<Point> operator+(int32_t const s, Point const &p);
    friend std::shared_ptr<Point> operator+(Point const &p, int32_t const s);
    friend std::ostream& operator<<(std::ostream& os, const Point &p);
    
    friend double operator*(const Point& p, const Vector &v);
    friend double operator*(const Vector &v, const Point& p);

};
#endif /* POINT_HPP */