#include "Matrix.hpp"
#include <math.h>
#include <iomanip>

Matrix::Matrix(){
    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 4; j++){
            mat[i][j] = 0;
        } 
    }
}

Matrix::~Matrix(){
    for (size_t i = 0; i < 4; i++){ 
        for (size_t j = 0; j < 4; j++){
            mat[i][j] = 0;
        } 
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix &m){
    os << std::setprecision(2);
    for (size_t i = 0; i < 4; i++){
        if(i == 0){
            os << "/ ";
        } else if(i == 3){
            os << "\\ ";
        } else{
            os << "| ";
        }

        for (size_t j = 0; j < 4; j++){
            os << m[i][j];
            if(j < 3){
                os << "\t";
            }
        }
        
        if(i == 0){
            os << " \\";
        } else if(i == 3){
            os << " /";
        } else{
            os << " |";
        }
        os << std::endl;
    }

    return os;
}

Matrix identity(){
    Matrix m = Matrix();
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;
    return m;
}

Matrix traslation(const double new_x, const double new_y, const double new_z){
    Matrix m = identity();
    m[0][3] = new_x;
    m[1][3] = new_y;
    m[2][3] = new_z;
    return m;
}

Matrix rotationX(const double angle){
    Matrix m = identity();
    m[1][1] = cos(angle);
    m[1][2] = -sin(angle);
    m[2][1] = sin(angle);
    m[2][2] = cos(angle);
    return m;
}

Matrix rotationY(const double angle){
    Matrix m = identity();
    m[0][0] = cos(angle);
    m[0][2] = sin(angle);
    m[2][0] = -sin(angle);
    m[2][2] = cos(angle);
    return m;
}

Matrix rotationZ(const double angle){
    Matrix m = identity();
    m[0][0] = cos(angle);
    m[0][1] = -sin(angle);
    m[1][0] = sin(angle);
    m[1][1] = cos(angle);
    return m;
}

Matrix scale(const double x_scale, const double y_scale, const double z_scale){
    Matrix m = identity();
    m[0][0] = x_scale;
    m[1][1] = y_scale;
    m[2][2] = z_scale;
    return m;
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
    Matrix result = Matrix();

    for (std::size_t i = 0; i < 4; i++) {
        for (std::size_t j = 0; j < 4; j++) {
            for (std::size_t k = 0; k < 4; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

Matrix operator*(const Matrix& m, const double c){
    Matrix result = Matrix();
    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 4; j++){
            result[i][j] = m[i][j] * c;
        } 
    }
    return result;
}

Matrix operator*(const double c, const Matrix& m){
    return m * c;
}



