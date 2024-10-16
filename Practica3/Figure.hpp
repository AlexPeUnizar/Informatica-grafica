#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "Ray.hpp"

class Figure{
private:
    /* data */
public:
    Figure(/* args */) = default;
    ~Figure() = default;
    virtual bool isIntersectedBy(const Ray& ray);
};

#endif /* FIGURE_HPP */