#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <vector>
#include <memory>
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
    virtual Color emission(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& light, const IntersectableFigure& scene) const = 0;
};


#endif /* MATERIAL_HPP */