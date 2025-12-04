/**
 * @file IntersectableFigure.hpp
 * @brief Declaraciones de clases para figuras intersectables en un sistema de gráficos por computadora.
 * 
 * Este archivo define las clases base y estructuras necesarias para representar figuras que pueden ser intersectadas por rayos,
 * asi como la informacion relevante de la interseccion, como el punto de interseccion, la normal y el material.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef INTERSECTABLEFIGURE_HPP
#define INTERSECTABLEFIGURE_HPP
#include <memory>
#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"

class Material;

/**
 * @brief Estructura que representa la informacion de una interseccion entre un rayo y una figura.
 * 
 * Esta estructura almacena el tiempo de interseccion (t), la normal en el punto de interseccion,
 * el punto de interseccion en si, el material de la figura y el nombre de la figura.
 */
struct Intersection{
    public:
        double t = 0;
        Vector normal = Vector();
        Point intersectionPoint = Point();
        std::shared_ptr<Material> material;
        std::string figureName = ""; 
};

/**
 * @brief Clase abstracta que define la interfaz para figuras que pueden ser intersectadas por rayos.
 * 
 * Esta clase proporciona un metodo virtual puro para verificar si un rayo intersecta con la figura,
 * y debe ser implementada por cualquier figura concreta que desee participar en el sistema de interseccion.
 */
class IntersectableFigure{
private:
    /* data */
public:
    IntersectableFigure(/* args */) = default;
    virtual ~IntersectableFigure() = default;
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const = 0;
    
};

#endif /* INTERSECTABLEFIGURE_HPP */