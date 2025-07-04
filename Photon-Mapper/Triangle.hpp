#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Figure.hpp"
#include "Point.hpp"

class Triangle : public Figure {
private:
    std::shared_ptr<Point> v0, v1, v2; // Los tres vértices del triángulo

public:
    Triangle(const std::shared_ptr<Point>& v0, const std::shared_ptr<Point>& v1, const std::shared_ptr<Point>& v2, const std::shared_ptr<Material>& material)
        : Figure(material), v0(v0), v1(v1), v2(v2) {}
    virtual ~Triangle() = default;

    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
    virtual void applyTransform(const Matrix& m) override;
};

#endif /* TRIANGLE_HPP */