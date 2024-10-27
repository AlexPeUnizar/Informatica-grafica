#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <iostream>
#include <memory>

class Matrix{
private:
    double mat[4][4];    
public:
    Matrix();
    ~Matrix();
    double* operator[](std::size_t idx ){ return mat[idx]; }
    const double* operator[](std::size_t idx ) const{ return mat[idx]; }
    friend std::ostream& operator<<(std::ostream& os, const Matrix &m);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m, const double c);
    friend Matrix operator*(const double c, const Matrix& m);
};

Matrix identity();
Matrix traslation(double new_x, double new_y, double new_z);

Matrix rotationX(double angle);
Matrix rotationY(double angle);
Matrix rotationZ(double angle);

Matrix scale(double x_scale, double y_scale, double z_scale);

#endif /* MATRIX_HPP */