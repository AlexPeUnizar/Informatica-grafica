#ifndef COLOR_HPP
#define COLOR_HPP
#include "Coordinate.hpp"

class Color: public Coordinate{
private:
public:
    double& r = x;
    double& g = y;
    double& b = z;

    Color(double r_, double g_, double b_): Coordinate(r_/255.0, g_/255.0, b_/255.0, 0){};
    Color() : Coordinate(0.0, 0.0, 0.0, 0.0){};
    Color(const Coordinate& c) : Color(c.x, c.y, c.z) {}
    Color(const Color& c) : Color(c.x, c.y, c.z) {}
    ~Color();    
    Color& operator=(const Color& c);
};

#endif /* COLOR_HPP */