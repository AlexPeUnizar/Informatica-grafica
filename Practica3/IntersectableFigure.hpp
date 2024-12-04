#ifndef INTERSECTABLEFIGURE_HPP
#define INTERSECTABLEFIGURE_HPP
#include <memory>
#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"

class Material;

class Intersection{
    public:
        double t = 0;
        Vector normal = Vector();
        Point intersectionPoint = Point();
        std::shared_ptr<Material> material;
        std::string figureName = ""; 
};

class IntersectableFigure{
private:
    /* data */
public:
    IntersectableFigure(/* args */) = default;
    ~IntersectableFigure() = default;
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const = 0;
    
};

#endif /* INTERSECTABLEFIGURE_HPP */