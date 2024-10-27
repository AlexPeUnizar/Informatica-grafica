#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>
#include "Matrix.hpp"

class Coordinate{
private:

protected:
    double w;
public:
    double x, y, z;
    Coordinate(double x, double y, double z, double w);
    Coordinate() = default;
    ~Coordinate();
    friend std::ostream& operator<<(std::ostream& os, const Coordinate &c);
    friend Matrix baseChange(const Coordinate& origin, const Coordinate& u, const Coordinate& v, const Coordinate& w);
    friend Coordinate operator*(const Matrix& m, const Coordinate& c);
};


#endif // COORDINATE_HPP
