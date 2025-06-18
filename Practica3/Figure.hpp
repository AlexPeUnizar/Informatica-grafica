/**
 * @file Figure.hpp
 * @brief Declaración de la clase base abstracta Figure para figuras geométricas en gráficos por computadora.
 * 
 * Esta clase sirve como interfaz para figuras que pueden ser intersectadas por rayos, 
 * proporcionando métodos para gestionar la visibilidad, el material y el color de la figura.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "IntersectableFigure.hpp"
#include "Color.hpp"
#include "Material.hpp"

/**
 * @class Figure
 * @brief Clase base abstracta para figuras geométricas que pueden ser intersectadas por rayos.
 *
 * Proporciona métodos para gestionar la visibilidad, el material y el color de la figura.
 * Sirve como interfaz para figuras derivadas en gráficos por computadora.
 * 
 * @see IntersectableFigure
 */
class Figure: public IntersectableFigure{
protected:
    bool visible = true;
    std::shared_ptr<Material> material;

public:
    Figure() = default;
    Figure(const std::shared_ptr<Material>& material);
    virtual ~Figure() = default;
    void setColor(double r, double g, double b);
    void setMaterial(const std::shared_ptr<Material>& material);
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override = 0;
    void setVisible(bool visible);
};

#endif /* FIGURE_HPP */