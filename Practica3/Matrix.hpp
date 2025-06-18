/**
 * @file Matrix.hpp
 * @brief Definición de la clase Matrix y funciones auxiliares para operaciones con matrices 4x4.
 * 
 * Este archivo contiene la declaración de la clase Matrix, que representa matrices de 4x4 de tipo double,
 * así como las funciones y operadores necesarios para realizar operaciones comunes en gráficos por computadora,
 * como identidad, traslación, rotación y escalado.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <iostream>
#include <memory>

/**
 * @class Matrix
 * @brief Clase que representa una matriz 4x4 de tipo double.
 * 
 * Esta clase proporciona métodos para crear matrices identidad, de traslación, rotación y escalado,
 * así como operadores para multiplicar matrices y escalar matrices por un escalar.
 */
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