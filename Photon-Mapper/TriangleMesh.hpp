/**
 * @file TriangleMesh.hpp
 * @brief Declaracion de la clase TriangleMesh para representar una malla de triángulos en gráficos por computadora.
 *
 * Esta clase permite almacenar y manipular una coleccion de triángulos definidos por vertices e indices,
 * facilitando operaciones como la interseccion con rayos y la gestion de materiales asociados a la malla.
 *
 * @author Alex
 * @date 18-6-2025
 */
#ifndef TRIANGLEMESH_HPP
#define TRIANGLEMESH_HPP

#include <vector>
#include <memory>
#include "Triangle.hpp"
#include "Figure.hpp"
#include "AABB.hpp"

/**
 * @brief Estructura BVHNode que representa un nodo en la jerarquía de volúmenes delimitadores (BVH).
 * 
 * Esta estructura almacena la caja delimitadora (AABB) del nodo, los índices de los nodos hijo izquierdo y derecho,
 * así como el rango de triángulos contenidos en el nodo si es una hoja.
 */
struct BVHNode {
    AABB box;
    int left = -1;
    int right = -1;
    int start = 0;
    int count = 0;
    bool isLeaf() const { return left < 0 && right < 0; }
};

/**
 * @class TriangleMesh
 * @brief Clase que representa una malla de triángulos en el espacio tridimensional.
 *
 * Esta clase permite definir una malla compuesta por multiples triángulos, cada uno definido por sus vertices e indices.
 * Proporciona metodos para verificar intersecciones con rayos y gestionar materiales asociados a la malla.
 *
 * @see Figure
 */
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
