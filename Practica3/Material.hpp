#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "IntersectableFigure.hpp"
#include "Light.hpp"

class Intersection;
class IntersectableFigure;

class Material{
private:
    /* data */
protected:
    Color color;
public:
    Material() = default;
    Material(const Color& color);
    ~Material() = default;
    void setColor(const Color& color);
    virtual Color emission(const Ray& ray, const Intersection& intersection, const Light& light, const IntersectableFigure& scene) const = 0;
};


#endif /* MATERIAL_HPP */