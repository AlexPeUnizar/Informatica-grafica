#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <vector>
#include <memory>
#include "IntersectableFigure.hpp"
#include "Light.hpp"

const int MAX_BOUNCES = 6;
const int MAX_PATHS = 1;

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
    Vector randomDirection(const Ray& ray, const Intersection& intersection) const;
    virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth = 0) const = 0;
    virtual Color brdf(const Ray& ray, const Intersection& intersection) const = 0;
    Color nextEvent(const std::vector<std::shared_ptr<Light>>& lights, const Intersection& intersection, const IntersectableFigure& scene) const;

};


#endif /* MATERIAL_HPP */