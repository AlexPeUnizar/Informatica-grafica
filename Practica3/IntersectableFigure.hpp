#ifndef INTERSECTABLEFIGURE_HPP
#define INTERSECTABLEFIGURE_HPP
#include "Ray.hpp"

class IntersectableFigure{
private:
    /* data */
public:
    IntersectableFigure(/* args */) = default;
    ~IntersectableFigure() = default;
    virtual bool isIntersectedBy(const Ray& ray) const = 0;
};

#endif /* INTERSECTABLEFIGURE_HPP */