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
        double b0 = 0, b1 = 0, b2 = 0;

};

class IntersectableFigure{
private:
    /* data */
public:
    IntersectableFigure(/* args */) = default;
    virtual ~IntersectableFigure() = default;
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const = 0;
    
};

#endif /* INTERSECTABLEFIGURE_HPP */