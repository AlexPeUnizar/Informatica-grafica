/**
 * @file Coordinate.hpp
 * @brief Declaracion de la clase Coordinate para coordenadas 3D homogeneas.
 * @author Alex
 * @date 18-6-2025
 */
#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <iostream>
#include "Matrix.hpp"

/**
 * @brief Declaracion de la clase Coordinate.
 * 
 * Esta clase representa un punto o vector en coordenadas homogeneas 3D.
 * Permite realizar operaciones aritmeticas y cambios de base.
 */
class Coordinate{
private:
    double w;
protected:
public:
    double x, y, z;
    Coordinate(double x, double y, double z, double w);
    Coordinate() = default;
    virtual ~Coordinate() = default;
    friend std::ostream& operator<<(std::ostream& os, const Coordinate &c);
    friend Matrix baseChange(const Coordinate& origin, const Coordinate& u, const Coordinate& v, const Coordinate& w);
    friend Coordinate operator*(const Matrix& m, const Coordinate& c);
    friend Coordinate operator*(const Coordinate& c1, const Coordinate& c2);
    friend Coordinate operator*(const Coordinate& c, const double constant);
    friend Coordinate operator*(const double constant, const Coordinate& c);
    friend Coordinate operator/(const Coordinate& c1, const Coordinate& c2);
    friend Coordinate operator/(const Coordinate& c, const double constant);
    friend Coordinate operator+(const Coordinate& c1, const Coordinate& c2);
    friend Coordinate operator+(const Coordinate& c, const double constant);
    friend Coordinate operator+(const double constant, const Coordinate& c);
    Coordinate& operator+=(const Coordinate& c);
    Coordinate& operator+=(const double constant);
    Coordinate& operator/=(const double c);
    Coordinate& operator*=(const double c);
    friend double maxComponent(const Coordinate& c);
    double& operator[](std::size_t idx);
    const double& operator[](std::size_t idx) const;

};


#endif // COORDINATE_HPP
