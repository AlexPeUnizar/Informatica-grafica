#ifndef RAY_HPP
#define RAY_HPP
#include "Point.hpp"
#include "Vector.hpp"

class Ray{
private:
public:
    Point origin;
    Vector dir;
    Ray(const Point& origin, const Vector& dir);
    Ray(/* args */) = default;
    ~Ray();
    friend std::ostream& operator<<(std::ostream& os, const Ray &r);
};

#endif /* RAY_HPP */