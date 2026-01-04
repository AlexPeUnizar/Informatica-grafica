/**
 * @file Matrix.cpp
 * @brief Implementacion de la clase Matrix para operaciones con matrices 4x4 utilizadas en transformaciones gráficas.
 * 
 * Este archivo contiene la implementacion de la clase Matrix, que proporciona funcionalidades para la creacion y manipulacion
 * de matrices 4x4, incluyendo operaciones de identidad, traslacion, rotacion, escalado y multiplicacion de matrices.
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
 * @brief Sobrecarga del operador de insercion para imprimir la matriz en un formato legible.
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
 * Esta funcion genera una matriz identidad, que es una matriz cuadrada con unos en la diagonal principal
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
 * @brief Transpone una matriz 4x4.
 *
 * Esta funcion intercambia las filas y columnas de una matriz
 */ 
Matrix transpose(const Matrix& m){
    Matrix result;
    for (std::size_t i = 0; i < 4; i++) {
        for (std::size_t j = 0; j < 4; j++) {
            result[i][j] = m[j][i];
        }
    }
    return result;
}

/**
 * @brief Crea una matriz de traslacion 4x4.
 *
 * Esta funcion genera una matriz de traslacion que desplaza un punto en el espacio tridimensional
 * por las distancias especificadas en los ejes x, y y z.
 * 
 * @param new_x Desplazamiento en el eje x.
 * @param new_y Desplazamiento en el eje y.
 * @param new_z Desplazamiento en el eje z.
 * @return Matrix Matriz de traslacion 4x4.
 */
Matrix traslation(const double new_x, const double new_y, const double new_z){
    Matrix m = identity();
    m[0][3] = new_x;
    m[1][3] = new_y;
    m[2][3] = new_z;
    return m;
}

/**
 * @brief Crea una matriz de rotacion alrededor del eje X.
 *
 * Esta funcion genera una matriz de rotacion que rota un punto en el espacio tridimensional
 * alrededor del eje X por un ángulo especificado en radianes.
 * 
 * @param angle Ángulo de rotacion en radianes.
 * @return Matrix Matriz de rotacion alrededor del eje X 4x4.
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
 * @brief Crea una matriz de rotacion alrededor del eje Y.
 *
 * Esta funcion genera una matriz de rotacion que rota un punto en el espacio tridimensional
 * alrededor del eje Y por un ángulo especificado en radianes.
 * 
 * @param angle Ángulo de rotacion en radianes.
 * @return Matrix Matriz de rotacion alrededor del eje Y 4x4.
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
 * @brief Crea una matriz de rotacion alrededor del eje Z.
 *
 * Esta funcion genera una matriz de rotacion que rota un punto en el espacio tridimensional
 * alrededor del eje Z por un ángulo especificado en radianes.
 * 
 * @param angle Ángulo de rotacion en radianes.
 * @return Matrix Matriz de rotacion alrededor del eje Z 4x4.
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
 * Esta funcion genera una matriz de escalado que escala un punto en el espacio tridimensional
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
 * @brief Sobrecarga del operador de multiplicacion de matrices.
 *
 * Este operador permite multiplicar dos matrices 4x4, realizando la operacion de producto matricial.
 * 
 * @param m1 Primera matriz a multiplicar.
 * @param m2 Segunda matriz a multiplicar.
 * @return Matrix Resultado de la multiplicacion de las dos matrices.
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
 * @brief Sobrecarga del operador de multiplicacion de una matriz por un escalar.
 *
 * Este operador permite multiplicar una matriz 4x4 por un escalar, escalando todos sus elementos.
 * 
 * @param m Matriz a multiplicar.
 * @param c Escalar por el cual se multiplica la matriz.
 * @return Matrix Resultado de la multiplicacion de la matriz por el escalar.
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
 * @brief Sobrecarga del operador de multiplicacion de un escalar por una matriz.
 *
 * Este operador permite multiplicar un escalar por una matriz 4x4, escalando todos sus elementos.
 * 
 * @param c Escalar por el cual se multiplica la matriz.
 * @param m Matriz a multiplicar.
 * @return Matrix Resultado de la multiplicacion del escalar por la matriz.
 */
Matrix operator*(const double c, const Matrix& m){
    return m * c;
}

/**
 * @brief Calcula la inversa de una matriz 4x4.
 *
 * Esta funcion calcula la inversa de una matriz 4x4 utilizando el metodo de cofactores y determinantes.
 * 
 * @param m Matriz a invertir.
 * @return Matrix Matriz inversa de la matriz dada.
 */
Matrix inverse(const Matrix& m){
    Matrix inv;
    double det;
    double invOut[16];

    const double* a = &m.mat[0][0]; // Acceso plano a los datos

    invOut[0] =  a[5]  * a[10] * a[15] - 
                 a[5]  * a[11] * a[14] - 
                 a[9]  * a[6]  * a[15] + 
                 a[9]  * a[7]  * a[14] +
                 a[13] * a[6]  * a[11] - 
                 a[13] * a[7]  * a[10];

    invOut[4] = -a[4]  * a[10] * a[15] + 
                 a[4]  * a[11] * a[14] + 
                 a[8]  * a[6]  * a[15] - 
                 a[8]  * a[7]  * a[14] - 
                 a[12] * a[6]  * a[11] + 
                 a[12] * a[7]  * a[10];

    invOut[8] =  a[4]  * a[9] * a[15] - 
                 a[4]  * a[11] * a[13] - 
                 a[8]  * a[5] * a[15] + 
                 a[8]  * a[7] * a[13] + 
                 a[12] * a[5] * a[11] - 
                 a[12] * a[7] * a[9];

    invOut[12] = -a[4]  * a[9] * a[14] + 
                  a[4]  * a[10] * a[13] +
                  a[8]  * a[5] * a[14] - 
                  a[8]  * a[6] * a[13] - 
                  a[12] * a[5] * a[10] + 
                  a[12] * a[6] * a[9];

    invOut[1] = -a[1]  * a[10] * a[15] + 
                 a[1]  * a[11] * a[14] + 
                 a[9]  * a[2] * a[15] - 
                 a[9]  * a[3] * a[14] - 
                 a[13] * a[2] * a[11] + 
                 a[13] * a[3] * a[10];

    invOut[5] =  a[0]  * a[10] * a[15] - 
                 a[0]  * a[11] * a[14] - 
                 a[8]  * a[2] * a[15] + 
                 a[8]  * a[3] * a[14] + 
                 a[12] * a[2] * a[11] - 
                 a[12] * a[3] * a[10];

    invOut[9] = -a[0]  * a[9] * a[15] + 
                 a[0]  * a[11] * a[13] + 
                 a[8]  * a[1] * a[15] - 
                 a[8]  * a[3] * a[13] - 
                 a[12] * a[1] * a[11] + 
                 a[12] * a[3] * a[9];

    invOut[13] = a[0]  * a[9] * a[14] - 
                 a[0]  * a[10] * a[13] - 
                 a[8]  * a[1] * a[14] + 
                 a[8]  * a[2] * a[13] + 
                 a[12] * a[1] * a[10] - 
                 a[12] * a[2] * a[9];

    invOut[2] =  a[1]  * a[6] * a[15] - 
                 a[1]  * a[7] * a[14] - 
                 a[5]  * a[2] * a[15] + 
                 a[5]  * a[3] * a[14] + 
                 a[13] * a[2] * a[7] - 
                 a[13] * a[3] * a[6];

    invOut[6] = -a[0]  * a[6] * a[15] + 
                 a[0]  * a[7] * a[14] + 
                 a[4]  * a[2] * a[15] - 
                 a[4]  * a[3] * a[14] - 
                 a[12] * a[2] * a[7] + 
                 a[12] * a[3] * a[6];

    invOut[10] = a[0]  * a[5] * a[15] - 
                 a[0]  * a[7] * a[13] - 
                 a[4]  * a[1] * a[15] + 
                 a[4]  * a[3] * a[13] + 
                 a[12] * a[1] * a[7] - 
                 a[12] * a[3] * a[5];

    invOut[14] = -a[0]  * a[5] * a[14] + 
                  a[0]  * a[6] * a[13] + 
                  a[4]  * a[1] * a[14] - 
                  a[4]  * a[2] * a[13] - 
                  a[12] * a[1] * a[6] + 
                  a[12] * a[2] * a[5];

    invOut[3] = -a[1] * a[6] * a[11] + 
                 a[1] * a[7] * a[10] + 
                 a[5] * a[2] * a[11] - 
                 a[5] * a[3] * a[10] - 
                 a[9] * a[2] * a[7] + 
                 a[9] * a[3] * a[6];

    invOut[7] =  a[0] * a[6] * a[11] - 
                 a[0] * a[7] * a[10] - 
                 a[4] * a[2] * a[11] + 
                 a[4] * a[3] * a[10] + 
                 a[8] * a[2] * a[7] - 
                 a[8] * a[3] * a[6];

    invOut[11] = -a[0] * a[5] * a[11] + 
                  a[0] * a[7] * a[9] + 
                  a[4] * a[1] * a[11] - 
                  a[4] * a[3] * a[9] - 
                  a[8] * a[1] * a[7] + 
                  a[8] * a[3] * a[5];

    invOut[15] = a[0] * a[5] * a[10] - 
                 a[0] * a[6] * a[9] - 
                 a[4] * a[1] * a[10] + 
                 a[4] * a[2] * a[9] + 
                 a[8] * a[1] * a[6] - 
                 a[8] * a[2] * a[5];

    det = a[0] * invOut[0] + a[1] * invOut[4] + a[2] * invOut[8] + a[3] * invOut[12];

    if (det == 0.0)
        throw std::runtime_error("Matrix is singular and cannot be inverted.");

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        reinterpret_cast<double*>(&inv)[i] = invOut[i] * det;

    return inv;
}