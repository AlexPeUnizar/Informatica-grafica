#ifndef RAY_HPP
#define RAY_HPP
#include "Point.hpp"
#include "Vector.hpp"
#include "Figure.hpp"

class Ray{
private:
public:
    Point origin;
    Vector dir;
    Ray(const Point& origin, const Vector& dir);
    Ray(/* args */) = default;
    ~Ray();
    bool intersect(Figure& figure);
};

#endif /* RAY_HPP */