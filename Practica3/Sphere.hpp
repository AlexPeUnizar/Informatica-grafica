#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Figure.hpp"
#include "Point.hpp"

class Sphere : public Figure{
private:
    Point origin;
    double r;
public:
    Sphere(const Point &origin, double r);
    Sphere(double x, double y, double z, double r):origin(Point(x, y, z)), r(r){};
    ~Sphere();
    virtual bool isIntersectedBy(const Ray& ray, double &t) const;
};

#endif /* SPHERE_HPP */