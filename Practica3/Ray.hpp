#ifndef RAY_HPP
#define RAY_HPP
#include "Point.hpp"
#include "Vector.hpp"

class Ray{
private:
    Point o;
    Vector d;
public:
    Ray(const Point& o, const Vector& d);
    Ray(/* args */);
    ~Ray();
};

#endif /* RAY_HPP */