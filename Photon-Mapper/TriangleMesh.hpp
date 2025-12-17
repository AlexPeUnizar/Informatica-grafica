#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include <vector>
#include <memory>
#include "Triangle.hpp"
#include "Figure.hpp"
#include "AABB.hpp"

struct BVHNode {
    AABB box;
    int left = -1;
    int right = -1;
    int start = 0;
    int count = 0;
    bool isLeaf() const { return left < 0 && right < 0; }
};

class TriangleMesh : public Figure {
    private:
        std::vector<std::shared_ptr<Triangle>> triangles;
    
        // BVH
        std::vector<int> triIndex;       // permutación de triángulos
        std::vector<BVHNode> nodes;
        int root = -1;
        int leafSize = 4;
    
        // helpers BVH
        AABB triBounds(int triId) const;
        Point triCentroid(int triId) const;
        int buildNode(int start, int end);
        void buildBVH();
    
    public:
        TriangleMesh(const std::shared_ptr<Material>& material)
            : Figure(material) {}
    
        static std::unique_ptr<TriangleMesh> fromOBJ(
            const std::string& path,
            const std::shared_ptr<Material>& material,
            bool smoothNormals,
            double scaleFactor = 1.0,
            Vector offset = Vector(0,0,0)
        );
        bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
        void addTriangle(const std::shared_ptr<Triangle>& t);
        virtual void applyTransform(const Matrix& t) override;
};

#endif /* TRIANGLEMESH_HPP */
