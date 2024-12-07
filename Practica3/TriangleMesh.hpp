#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include <vector>
#include <memory>
#include "Triangle.hpp"
#include "Figure.hpp"

class TriangleMesh : public Figure {
private:
    std::vector<std::shared_ptr<Point>> vertices;          // Lista de vértices
    std::vector<int> indices;            // Índices que definen triángulos
    std::vector<std::shared_ptr<Triangle>> triangles; // Triángulos individuales
    std::shared_ptr<Material> material;  // Material para toda la malla

public:
    TriangleMesh(const std::vector<std::shared_ptr<Point>>& vertices, 
                 const std::vector<int>& indices, 
                 const std::shared_ptr<Material>& material);

    virtual ~TriangleMesh();

    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;

    void addTriangle(const Point& v0, const Point& v1, const Point& v2);
};

#endif /* TRIANGLEMESH_HPP */
