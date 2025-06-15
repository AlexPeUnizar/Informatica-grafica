#ifndef PLANE_HPP
#define PLANE_HPP
#include "Figure.hpp"
#include "Vector.hpp"
#include "Point.hpp"

class Plane: public Figure{
private:
    Vector normal;
    double dist;

public:
    Plane(const Vector& normal, const double dist, const std::shared_ptr<Material>& material);
    /*
    Plane(const Point& p1, const Point& p2, const Point& p3);
    Plane(const Vector& t1, const Vector& t2);
    Plane(const Vector& normal);
    */
    Plane() = default;
    ~Plane();
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
    virtual void applyTransform(const Matrix& t) override;
};

   

#endif /* PLANE_HPP */