#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Figure.hpp"
#include "Point.hpp"

class Sphere : Figure{
private:
    Point o;
    double r;
public:
    Sphere(const Point &o, double r);
    Sphere(double x, double y, double z, double r):o(Point(x, y, z)), r(r){};
    ~Sphere();
    bool intersect();
};

#endif /* SPHERE_HPP */