#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Figure.hpp"
#include "Point.hpp"

class Sphere : public Figure{
private:
    Point origin;
    double r;
public:
    Sphere(const Point &origin, double r, const std::shared_ptr<Material>& material);
    Sphere(double x, double y, double z, double r, const std::shared_ptr<Material>& material): Figure(material), origin(Point(x, y, z)), r(r){};
    ~Sphere();
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
    virtual void applyTransform(const Matrix& t) override;
};

#endif /* SPHERE_HPP */