#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "IntersectableFigure.hpp"


class Figure: public IntersectableFigure{
protected:
    struct Color{
        double r;
        double g;
        double b;
    };

    Color color = {0,0,0};
public:
    Figure(/* args */) = default;
    ~Figure() = default;
    void setColor(double r,double g, double b);
    virtual bool isIntersectedBy(const Ray& ray) const = 0;
};

#endif /* FIGURE_HPP */