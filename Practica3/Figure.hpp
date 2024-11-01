#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "IntersectableFigure.hpp"
#include "Color.hpp"
#include "Material.hpp"

class Figure: public IntersectableFigure{
protected:
    Color color;
    bool visible = true;
    std::shared_ptr<Material> material;

public:
    Figure(/* args */) = default;
    virtual ~Figure() = default;
    void setColor(double r, double g, double b);
    virtual bool isIntersectedBy(const Ray& ray, Intersection& intersection) const = 0;
    double getR();
    double getG();
    double getB();
    Color getColor();
    void setVisible(bool visible);
};

#endif /* FIGURE_HPP */