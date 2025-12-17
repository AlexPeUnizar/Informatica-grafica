#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Figure.hpp"
#include "Point.hpp"

class Triangle : public Figure {
private:
    Point v0, v1, v2;
    Vector n0, n1, n2;
    bool hasVertexNormals = false;

public:
    // Triángulo sin normales (flat)
    Triangle(const Point& v0, const Point& v1, const Point& v2,
                const std::shared_ptr<Material>& material)
        : Figure(material), v0(v0), v1(v1), v2(v2) {}

    // Triángulo con normales por vértice (smooth)
    Triangle(const Point& v0, const Point& v1, const Point& v2,
                const Vector& n0, const Vector& n1, const Vector& n2,
                const std::shared_ptr<Material>& material)
        : Figure(material), v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2),
            hasVertexNormals(true) {}

    bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;

    Point getV0() const { return v0; }
    Point getV1() const { return v1; }
    Point getV2() const { return v2; }
    virtual void applyTransform(const Matrix& m) override;
};

#endif /* TRIANGLE_HPP */