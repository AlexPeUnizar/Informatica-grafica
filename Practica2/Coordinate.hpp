#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>
#include "Matrix.hpp"

class Coordinate{
private:

protected:
    double x, y, z, w;
public:
    Coordinate(double x, double y, double z, double w);
    Coordinate();
    ~Coordinate();
    friend std::ostream& operator<<(std::ostream& os, const Coordinate &c);
    friend std::shared_ptr<Matrix> baseChange(const Coordinate& origin, const Coordinate& u, const Coordinate& v, const Coordinate& w);
    friend std::shared_ptr<Coordinate> operator*(const Matrix& m, const Coordinate& c);
};


#endif // COORDINATE_HPP
