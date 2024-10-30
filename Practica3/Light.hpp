#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "Point.hpp"
#include "Color.hpp"

class Light{
private:
    Point center;
    Color power;
public:
    Light(Point center, Color Power);
    Light();
    ~Light();
};

#endif /* LIGHT_HPP */