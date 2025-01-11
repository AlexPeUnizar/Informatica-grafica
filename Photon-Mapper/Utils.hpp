#ifndef UTILS_HPP
#define UTILS_HPP
#include "Point.hpp"
#include "Vector.hpp"

double randomDouble(double min, double max);
double randomDouble();
Vector randomDirection();
Vector randomDirection(const Point& point, const Vector& normal);
#endif /* UTILS_HPP */