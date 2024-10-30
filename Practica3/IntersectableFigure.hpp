#ifndef INTERSECTABLEFIGURE_HPP
#define INTERSECTABLEFIGURE_HPP
#include "Ray.hpp"
#include "Color.hpp"

class IntersectableFigure{
private:
    /* data */
public:
    struct Intersection{
        double t = 0;
        Vector normal = Vector();
        Point intersectionPoint = Point();
        Color color;
    };
    IntersectableFigure(/* args */) = default;
    ~IntersectableFigure() = default;
    virtual bool isIntersectedBy(const Ray& ray, Intersection& intersection) const = 0;
    
};

#endif /* INTERSECTABLEFIGURE_HPP */