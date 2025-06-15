#include "TriangleMesh.hpp"

TriangleMesh::TriangleMesh(const std::vector<std::shared_ptr<Point>>& vertices, 
                           const std::vector<int>& indices, 
                           const std::shared_ptr<Material>& material) 
    : vertices(vertices), indices(indices), material(material) {

    // Crear triángulos a partir de la lista de índices
    for (size_t i = 0; i < indices.size(); i += 3) {
        auto v0 = vertices[indices[i]];
        auto v1 = vertices[indices[i + 1]];
        auto v2 = vertices[indices[i + 2]];
        triangles.push_back(std::make_shared<Triangle>(*v0, *v1, *v2, material));
    }
}

TriangleMesh::~TriangleMesh(){
    for(size_t i = 0; i < triangles.size(); i++){
        triangles[i]->~Triangle();
    }
    triangles.clear();
    indices.clear();
}

void TriangleMesh::addTriangle(const Point& v0, const Point& v1, const Point& v2) {
    triangles.push_back(std::make_shared<Triangle>(v0, v1, v2, material));
}

bool TriangleMesh::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const {
    bool hitAnything = false;
    double closestSoFar = tMax;

    for (const auto& triangle : triangles) {
        Intersection tempIntersection;
        if (triangle->isIntersectedBy(ray, tMin, closestSoFar, tempIntersection)) {
            hitAnything = true;
            closestSoFar = tempIntersection.t;
            intersection = tempIntersection;
        }
    }

    return hitAnything;
}

void TriangleMesh::applyTransform(const Matrix& t) {
    for (auto& triangle : triangles) {
        triangle->applyTransform(t);
    }
}
