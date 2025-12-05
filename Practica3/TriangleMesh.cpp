/**
 * @file TriangleMesh.cpp
 * @brief Implementacion de la clase TriangleMesh para la gestion y manipulacion de mallas triangulares en gráficos por computadora.
 * 
 * Este archivo contiene la definicion de los metodos de la clase TriangleMesh, que permite crear, almacenar y gestionar colecciones de triángulos a partir de vertices e indices, asi como realizar pruebas de interseccion con rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "TriangleMesh.hpp"

/** 
 * @brief Constructor de la clase TriangleMesh.
 * 
 * Este constructor inicializa una malla de triángulos a partir de una lista de vertices y una lista de indices que definen los triángulos.
 * Tambien se asigna un material a toda la malla.
 * 
 * @param vertices Lista de vertices que componen la malla.
 * @param indices Lista de indices que definen los triángulos en la malla.
 * @param material Material asociado a toda la malla.
 */
TriangleMesh::TriangleMesh(const std::vector<std::shared_ptr<Point>>& vertices, 
                           const std::vector<int>& indices, 
                           const std::shared_ptr<Material>& material) 
    : vertices(vertices), indices(indices), material(material) {

    // Crear triángulos a partir de la lista de indices
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
 * Se asegura de llamar al destructor de cada triángulo y limpiar las listas de triángulos e indices.
 */
TriangleMesh::~TriangleMesh(){
    /*
    for(size_t i = 0; i < triangles.size(); i++){
        triangles[i]->~Triangle();
    } 
    */
    triangles.clear();
    indices.clear();
}

/**
 * @brief Metodo que verifica si un rayo intersecta con la malla de triángulos.
 * 
 * Este metodo recorre todos los triángulos de la malla y verifica si el rayo intersecta con alguno de ellos.
 * Si se encuentra una interseccion, se actualiza el objeto `intersection` con la informacion de la interseccion más cercana.
 * 
 * @param ray Rayo que se está verificando para la interseccion.
 * @param tMin Valor minimo de t para considerar la interseccion.
 * @param tMax Valor máximo de t para considerar la interseccion.
 * @param intersection Estructura donde se almacenarán los detalles de la interseccion si ocurre.
 * @return bool Verdadero si hay una interseccion válida, falso en caso contrario.
 */
void TriangleMesh::addTriangle(const Point& v0, const Point& v1, const Point& v2) {
    triangles.push_back(std::make_shared<Triangle>(v0, v1, v2, material));
}

/**
 * @brief Comprueba si un rayo intersecta con la malla de triángulos.
 * 
 * Este metodo recorre todos los triángulos de la malla y verifica si el rayo intersecta con alguno de ellos.
 * Si se encuentra una interseccion, se actualiza el objeto `intersection` con la informacion de la interseccion más cercana.
 * 
 * @param ray Rayo que se está verificando para la interseccion.
 * @param tMin Valor minimo de t para considerar la interseccion.
 * @param tMax Valor máximo de t para considerar la interseccion.
 * @param intersection Estructura donde se almacenarán los detalles de la interseccion si ocurre.
 * @return bool Verdadero si hay una interseccion válida, falso en caso contrario.
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
