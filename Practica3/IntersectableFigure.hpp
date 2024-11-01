#ifndef INTERSECTABLEFIGURE_HPP
#define INTERSECTABLEFIGURE_HPP
#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"

class Intersection{
    public:
        double t = 0;
        Vector normal = Vector();
        Point intersectionPoint = Point();
        std::shared_ptr<Material> material;
};

class IntersectableFigure{
private:
    /* data */
public:
    IntersectableFigure(/* args */) = default;
    ~IntersectableFigure() = default;
    virtual bool isIntersectedBy(const Ray& ray, Intersection& intersection) const = 0;
    
};

#endif /* INTERSECTABLEFIGURE_HPP */