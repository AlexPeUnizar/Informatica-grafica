/**
 * @file TriangleMesh.cpp
 * @brief Implementación de la clase TriangleMesh para la gestión y manipulación de mallas triangulares en gráficos por computadora.
 * 
 * Este archivo contiene la definición de los métodos de la clase TriangleMesh, que permite crear, almacenar y gestionar colecciones de triángulos a partir de vértices e índices, así como realizar pruebas de intersección con rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "TriangleMesh.hpp"

/** 
 * @brief Constructor de la clase TriangleMesh.
 * 
 * Este constructor inicializa una malla de triángulos a partir de una lista de vértices y una lista de índices que definen los triángulos.
 * También se asigna un material a toda la malla.
 * 
 * @param vertices Lista de vértices que componen la malla.
 * @param indices Lista de índices que definen los triángulos en la malla.
 * @param material Material asociado a toda la malla.
 */
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

/**
 * @brief Destructor de la clase TriangleMesh.
 * 
 * Este destructor libera los recursos asociados con los triángulos almacenados en la malla.
 * Se asegura de llamar al destructor de cada triángulo y limpiar las listas de triángulos e índices.
 */
TriangleMesh::~TriangleMesh(){
    for(size_t i = 0; i < triangles.size(); i++){
        triangles[i]->~Triangle();
    }
    triangles.clear();
    indices.clear();
}

/**
 * @brief Método que verifica si un rayo intersecta con la malla de triángulos.
 * 
 * Este método recorre todos los triángulos de la malla y verifica si el rayo intersecta con alguno de ellos.
 * Si se encuentra una intersección, se actualiza el objeto `intersection` con la información de la intersección más cercana.
 * 
 * @param ray Rayo que se está verificando para la intersección.
 * @param tMin Valor mínimo de t para considerar la intersección.
 * @param tMax Valor máximo de t para considerar la intersección.
 * @param intersection Estructura donde se almacenarán los detalles de la intersección si ocurre.
 * @return bool Verdadero si hay una intersección válida, falso en caso contrario.
 */
void TriangleMesh::addTriangle(const Point& v0, const Point& v1, const Point& v2) {
    triangles.push_back(std::make_shared<Triangle>(v0, v1, v2, material));
}

/**
 * @brief Comprueba si un rayo intersecta con la malla de triángulos.
 * 
 * Este método recorre todos los triángulos de la malla y verifica si el rayo intersecta con alguno de ellos.
 * Si se encuentra una intersección, se actualiza el objeto `intersection` con la información de la intersección más cercana.
 * 
 * @param ray Rayo que se está verificando para la intersección.
 * @param tMin Valor mínimo de t para considerar la intersección.
 * @param tMax Valor máximo de t para considerar la intersección.
 * @param intersection Estructura donde se almacenarán los detalles de la intersección si ocurre.
 * @return bool Verdadero si hay una intersección válida, falso en caso contrario.
 */
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
