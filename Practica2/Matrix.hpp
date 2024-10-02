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
    friend std::shared_ptr<Matrix> operator*(const Matrix& m1, const Matrix& m2);
    friend std::shared_ptr<Matrix> operator*(const Matrix& m, const double c);
    friend std::shared_ptr<Matrix> operator*(const double c, const Matrix& m);
};

std::shared_ptr<Matrix> identity();
std::shared_ptr<Matrix> traslation(double new_x, double new_y, double new_z);

std::shared_ptr<Matrix> rotationX(double angle);
std::shared_ptr<Matrix> rotationY(double angle);
std::shared_ptr<Matrix> rotationZ(double angle);

std::shared_ptr<Matrix> scale(double x_scale, double y_scale, double z_scale);

#endif /* MATRIX_HPP */