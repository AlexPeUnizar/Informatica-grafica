#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Figure.hpp"
#include "Point.hpp"

class Cylinder : public Figure {
private:
    Point baseCenter; // Centro de la base del cilindro
    Vector axis;      // Dirección del eje del cilindro (debe ser normalizada)
    double radius;    // Radio del cilindro
    double height;    // Altura del cilindro

public:
    Cylinder(const Point& baseCenter, const Vector& axis, double radius, double height, const std::shared_ptr<Material>& material)
        : Figure(material), baseCenter(baseCenter), axis(normalize(axis)), radius(radius), height(height) {}

    ~Cylinder() = default;

    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
    virtual void applyTransform(const Matrix& t) override;
};


#endif /* CYLINDER_HPP */