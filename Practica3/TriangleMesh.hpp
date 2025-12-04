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
    std::vector<std::shared_ptr<Point>> vertices;          // Lista de vertices
    std::vector<int> indices;            // indices que definen triángulos
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
