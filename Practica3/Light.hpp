#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "Point.hpp"
#include "Color.hpp"

class Light{
private:
    Point center;
    Color power;
public:
    Light(const Point& center, const Color& power);
    Light();
    ~Light();
    Point& getCenter();
    Color& getPower();
};

#endif /* LIGHT_HPP */