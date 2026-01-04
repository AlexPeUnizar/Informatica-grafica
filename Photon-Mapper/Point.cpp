/**
 * @file Point.cpp
 * @brief Implementacion de las operaciones y sobrecarga de operadores para la clase Point.
 * 
 * Este archivo contiene las definiciones de las funciones relacionadas con la clase Point,
 * incluyendo la sobrecarga de operadores para facilitar operaciones matemáticas y de salida.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Point.hpp"

/**
 * @brief Constructor de la clase Point.
 * 
 * Inicializa un punto con coordenadas (x, y, z) y una componente homogenea w.
 * 
 * @param x Coordenada x del punto.
 * @param y Coordenada y del punto.
 * @param z Coordenada z del punto.
 */
std::ostream& operator<<(std::ostream& os, const Point &p){
    os << "Point(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

/**
 * @brief Sobrecarga del operador de resta para calcular la diferencia entre dos puntos.
 * 
 * Esta funcion calcula el vector que va desde el punto p2 al punto p1.
 * 
 * @param p1 Primer punto.
 * @param p2 Segundo punto.
 * @return Vector Resultado de la resta de los dos puntos.
 */
Vector operator-(Point const &p1, Point const &p2){
    return Vector(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
}

/**
 * @brief Sobrecarga del operador de suma para sumar un escalar a un punto.
 * 
 * Esta funcion permite sumar un escalar a las coordenadas de un punto, desplazando el punto en todas las direcciones.
 * 
 * @param s Escalar a sumar.
 * @param p Punto al que se le suma el escalar.
 * @return Point Resultado de la suma del escalar al punto.
 */
Point operator+(double const s, Point const &p){
    return Point(s+p.x, s+p.y, s+p.z);
}

/**
 * @brief Sobrecarga del operador de suma para sumar un escalar a un punto.
 * 
 * Esta funcion permite sumar un escalar a las coordenadas de un punto, desplazando el punto en todas las direcciones.
 * 
 * @param p Punto al que se le suma el escalar.
 * @param s Escalar a sumar.
 * @return Point Resultado de la suma del escalar al punto.
 */
Point operator+(Point const &p, double const s){
    return s+p;
}

/**
 * @brief Sobrecarga del operador de multiplicacion para calcular el producto punto entre un punto y un vector.
 * 
 * Esta funcion calcula el producto punto entre un punto y un vector, considerando el punto como un vector desde el origen.
 * 
 * @param p Punto que se multiplica por el vector.
 * @param v Vector con el que se multiplica el punto.
 * @return double Resultado del producto punto.
 */
double operator*(const Point& p, const Vector &v){
    return v*p;
}

/**
 * @brief Sobrecarga del operador de multiplicacion para calcular el producto punto entre un vector y un punto.
 * 
 * Esta funcion calcula el producto punto entre un vector y un punto, considerando el punto como un vector desde el origen.
 * 
 * @param v Vector que se multiplica por el punto.
 * @param p Punto con el que se multiplica el vector.
 * @return double Resultado del producto punto.
 */
double operator*(const Vector &v, const Point& p){
    return dotProduct(v, p - Point(0, 0, 0));
}

/**
 * @brief Operador de indexacion para la clase Point.
 * 
 * Esta funcion permite acceder a las componentes x, y, z del objeto Point
 * utilizando un indice (0 para x, 1 para y, 2 para z).
 * 
 * @param idx Indice de la componente a acceder (0, 1, o 2).
 * @return Referencia a la componente correspondiente del objeto Point.
 * @throw Excepcion si el indice es invalido.
 */
double& Point::operator[](std::size_t idx){
    switch (idx){
        case 0:
            return this->x;
            break;
        case 1:
            return this->y;
            break;
        case 2:
            return this->z;
            break;
        default:
            throw -1;
            break;
    }
}

/**
 * @brief Operador de indexacion constante para la clase Point.
 * 
 * Esta funcion permite acceder a las componentes x, y, z del objeto Point
 * utilizando un indice (0 para x, 1 para y, 2 para z) en un contexto constante.
 * 
 * @param idx Indice de la componente a acceder (0, 1, o 2).
 * @return Referencia constante a la componente correspondiente del objeto Point.
 * @throw Excepcion si el indice es invalido.
 */
const double& Point::operator[](std::size_t idx) const{
    switch (idx){
        case 0:
            return this->x;
            break;
        case 1:
            return this->y;
            break;
        case 2:
            return this->z;
            break;
        default:
            throw -1;
            break;
    }
}
