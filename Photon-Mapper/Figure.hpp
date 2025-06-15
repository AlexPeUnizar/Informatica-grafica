#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "IntersectableFigure.hpp"
#include "Color.hpp"
#include "Material.hpp"

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
    virtual void applyTransform(const Matrix& t) = 0;
    void setVisible(bool visible);
};

#endif /* FIGURE_HPP */