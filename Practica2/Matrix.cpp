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

std::shared_ptr<Matrix> identity(){
    std::shared_ptr<Matrix> m = std::make_shared<Matrix>();
    (*m)[0][0] = 1;
    (*m)[1][1] = 1;
    (*m)[2][2] = 1;
    (*m)[3][3] = 1;
    return m;
}

std::shared_ptr<Matrix> traslation(const double new_x, const double new_y, const double new_z){
    std::shared_ptr<Matrix> m = identity();
    (*m)[0][3] = new_x;
    (*m)[1][3] = new_y;
    (*m)[2][3] = new_z;
    return m;
}

std::shared_ptr<Matrix> rotationX(const double angle){
    std::shared_ptr<Matrix> m = identity();
    (*m)[1][1] = cos(angle);
    (*m)[1][2] = -sin(angle);
    (*m)[2][1] = sin(angle);
    (*m)[2][2] = cos(angle);
    return m;
}

std::shared_ptr<Matrix> rotationY(const double angle){
    std::shared_ptr<Matrix> m = identity();
    (*m)[0][0] = cos(angle);
    (*m)[0][2] = sin(angle);
    (*m)[2][0] = -sin(angle);
    (*m)[2][2] = cos(angle);
    return m;
}

std::shared_ptr<Matrix> rotationZ(const double angle){
    std::shared_ptr<Matrix> m = identity();
    (*m)[0][0] = cos(angle);
    (*m)[0][1] = -sin(angle);
    (*m)[1][0] = sin(angle);
    (*m)[1][1] = cos(angle);
    return m;
}

std::shared_ptr<Matrix> scale(const double x_scale, const double y_scale, const double z_scale){
    std::shared_ptr<Matrix> m = identity();
    (*m)[0][0] = x_scale;
    (*m)[1][1] = y_scale;
    (*m)[2][2] = z_scale;
    return m;
}

std::shared_ptr<Matrix> operator*(const Matrix& m1, const Matrix& m2){
    std::shared_ptr<Matrix> result = std::make_shared<Matrix>();

    for (std::size_t i = 0; i < 4; i++) {
        for (std::size_t j = 0; j < 4; j++) {
            for (std::size_t k = 0; k < 4; k++) {
                (*result)[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

std::shared_ptr<Matrix> operator*(const Matrix& m, const double c){
    std::shared_ptr<Matrix> result = std::make_shared<Matrix>();
    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 4; j++){
            (*result)[i][j] = m[i][j] * c;
        } 
    }
    return result;
}

std::shared_ptr<Matrix> operator*(const double c, const Matrix& m){
    return m * c;
}



