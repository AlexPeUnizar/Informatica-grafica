#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>
#include "Matrix.hpp"

class Coordinate{
private:
    double w;
protected:
public:
    double x, y, z;
    Coordinate(double x, double y, double z, double w);
    Coordinate() = default;
    ~Coordinate();
    friend std::ostream& operator<<(std::ostream& os, const Coordinate &c);
    friend Matrix baseChange(const Coordinate& origin, const Coordinate& u, const Coordinate& v, const Coordinate& w);
    friend Coordinate operator*(const Matrix& m, const Coordinate& c);
    friend Coordinate operator*(const Coordinate& c1, const Coordinate& c2);
    friend Coordinate operator*(const Coordinate& c, const double constant);
    friend Coordinate operator*(const double constant, const Coordinate& c);
    friend Coordinate operator/(const Coordinate& c1, const Coordinate& c2);
    friend Coordinate operator/(const Coordinate& c, const double constant);
    Coordinate& operator=(const Coordinate& t);
};


#endif // COORDINATE_HPP
