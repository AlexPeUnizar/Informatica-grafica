/**
 * @file Matrix.cpp
 * @brief Implementación de la clase Matrix para operaciones con matrices 4x4 utilizadas en transformaciones gráficas.
 * 
 * Este archivo contiene la implementación de la clase Matrix, que proporciona funcionalidades para la creación y manipulación
 * de matrices 4x4, incluyendo operaciones de identidad, traslación, rotación, escalado y multiplicación de matrices.
 * Está orientado a su uso en aplicaciones de informática gráfica y transformaciones en el espacio tridimensional.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Matrix.hpp"
#include <math.h>
#include <iomanip>

/**
 * @brief Constructor por defecto de la clase Matrix.
 *
 */
Matrix::Matrix(){
    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 4; j++){
            mat[i][j] = 0;
        } 
    }
}

/**
 * @brief Destructor de la clase Matrix.
 *
 * Este destructor limpia los valores de la matriz a cero.
 */
Matrix::~Matrix(){
    for (size_t i = 0; i < 4; i++){ 
        for (size_t j = 0; j < 4; j++){
            mat[i][j] = 0;
        } 
    }
}

/**
 * @brief Sobrecarga del operador de inserción para imprimir la matriz en un formato legible.
 *
 * Este operador permite imprimir la matriz en un formato estructurado, con bordes y tabulaciones.
 * 
 * @param os Flujo de salida donde se imprimirá la matriz.
 * @param m Matriz a imprimir.
 * @return std::ostream& Flujo de salida modificado.
 */
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

/**
 * @brief Crea una matriz identidad 4x4.
 *
 * Esta función genera una matriz identidad, que es una matriz cuadrada con unos en la diagonal principal
 * y ceros en el resto de las posiciones.
 * 
 * @return Matrix Matriz identidad 4x4.
 */
Matrix identity(){
    Matrix m = Matrix();
    m[0][0] = 1;
    m[1][1] = 1;
    m[2][2] = 1;
    m[3][3] = 1;
    return m;
}

/**
 * @brief Crea una matriz de traslación 4x4.
 *
 * Esta función genera una matriz de traslación que desplaza un punto en el espacio tridimensional
 * por las distancias especificadas en los ejes x, y y z.
 * 
 * @param new_x Desplazamiento en el eje x.
 * @param new_y Desplazamiento en el eje y.
 * @param new_z Desplazamiento en el eje z.
 * @return Matrix Matriz de traslación 4x4.
 */
Matrix traslation(const double new_x, const double new_y, const double new_z){
    Matrix m = identity();
    m[0][3] = new_x;
    m[1][3] = new_y;
    m[2][3] = new_z;
    return m;
}

/**
 * @brief Crea una matriz de rotación alrededor del eje X.
 *
 * Esta función genera una matriz de rotación que rota un punto en el espacio tridimensional
 * alrededor del eje X por un ángulo especificado en radianes.
 * 
 * @param angle Ángulo de rotación en radianes.
 * @return Matrix Matriz de rotación alrededor del eje X 4x4.
 */
Matrix rotationX(const double angle){
    Matrix m = identity();
    m[1][1] = cos(angle);
    m[1][2] = -sin(angle);
    m[2][1] = sin(angle);
    m[2][2] = cos(angle);
    return m;
}

/**
 * @brief Crea una matriz de rotación alrededor del eje Y.
 *
 * Esta función genera una matriz de rotación que rota un punto en el espacio tridimensional
 * alrededor del eje Y por un ángulo especificado en radianes.
 * 
 * @param angle Ángulo de rotación en radianes.
 * @return Matrix Matriz de rotación alrededor del eje Y 4x4.
 */
Matrix rotationY(const double angle){
    Matrix m = identity();
    m[0][0] = cos(angle);
    m[0][2] = sin(angle);
    m[2][0] = -sin(angle);
    m[2][2] = cos(angle);
    return m;
}

/**
 * @brief Crea una matriz de rotación alrededor del eje Z.
 *
 * Esta función genera una matriz de rotación que rota un punto en el espacio tridimensional
 * alrededor del eje Z por un ángulo especificado en radianes.
 * 
 * @param angle Ángulo de rotación en radianes.
 * @return Matrix Matriz de rotación alrededor del eje Z 4x4.
 */
Matrix rotationZ(const double angle){
    Matrix m = identity();
    m[0][0] = cos(angle);
    m[0][1] = -sin(angle);
    m[1][0] = sin(angle);
    m[1][1] = cos(angle);
    return m;
}

/**
 * @brief Crea una matriz de escalado 4x4.
 *
 * Esta función genera una matriz de escalado que escala un punto en el espacio tridimensional
 * por los factores especificados en los ejes x, y y z.
 * 
 * @param x_scale Factor de escalado en el eje x.
 * @param y_scale Factor de escalado en el eje y.
 * @param z_scale Factor de escalado en el eje z.
 * @return Matrix Matriz de escalado 4x4.
 */
Matrix scale(const double x_scale, const double y_scale, const double z_scale){
    Matrix m = identity();
    m[0][0] = x_scale;
    m[1][1] = y_scale;
    m[2][2] = z_scale;
    return m;
}

/**
 * @brief Sobrecarga del operador de multiplicación de matrices.
 *
 * Este operador permite multiplicar dos matrices 4x4, realizando la operación de producto matricial.
 * 
 * @param m1 Primera matriz a multiplicar.
 * @param m2 Segunda matriz a multiplicar.
 * @return Matrix Resultado de la multiplicación de las dos matrices.
 */
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

/**
 * @brief Sobrecarga del operador de multiplicación de una matriz por un escalar.
 *
 * Este operador permite multiplicar una matriz 4x4 por un escalar, escalando todos sus elementos.
 * 
 * @param m Matriz a multiplicar.
 * @param c Escalar por el cual se multiplica la matriz.
 * @return Matrix Resultado de la multiplicación de la matriz por el escalar.
 */
Matrix operator*(const Matrix& m, const double c){
    Matrix result = Matrix();
    for (size_t i = 0; i < 4; i++){
        for (size_t j = 0; j < 4; j++){
            result[i][j] = m[i][j] * c;
        } 
    }
    return result;
}

/**
 * @brief Sobrecarga del operador de multiplicación de un escalar por una matriz.
 *
 * Este operador permite multiplicar un escalar por una matriz 4x4, escalando todos sus elementos.
 * 
 * @param c Escalar por el cual se multiplica la matriz.
 * @param m Matriz a multiplicar.
 * @return Matrix Resultado de la multiplicación del escalar por la matriz.
 */
Matrix operator*(const double c, const Matrix& m){
    return m * c;
}



