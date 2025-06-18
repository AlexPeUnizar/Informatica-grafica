/**
 * @file Coordinate.cpp
 * @brief Implementación de la clase Coordinate y operaciones relacionadas para gráficos 3D.
 *
 * Este archivo define la clase Coordinate, que representa un punto o vector en coordenadas homogéneas 3D,
 * y proporciona sobrecargas de operadores y funciones utilitarias para manipular coordenadas y realizar
 * transformaciones matriciales.
 *
 * @author Alex
 * @date 18-6-2025
 */
 
#include "Coordinate.hpp"

/**
 * @brief Constructor de la clase Coordinate.
 * 
 * Crea un nuevo objeto Coordinate con los valores proporcionados para x, y, z y w.
 * 
 * @param x Valor de la coordenada x.
 * @param y Valor de la coordenada y.
 * @param z Valor de la coordenada z.
 * @param w Valor de la coordenada homogénea w.
 */
Coordinate::Coordinate(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

/**
 * @brief Destructor de la clase Coordinate.
 * 
 * Libera los recursos asociados con el objeto Coordinate.
 */
Coordinate::~Coordinate(){
}

/**
 * @brief Sobrecarga del operador de inserción para imprimir un objeto Coordinate.
 * 
 * Permite imprimir un objeto Coordinate en un flujo de salida, mostrando sus componentes x, y, z y w.
 * 
 * @param os Flujo de salida donde se imprimirá el objeto.
 * @param c Objeto Coordinate a imprimir.
 * @return Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const Coordinate &c){
    os << "Coordinate(" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ")";
    return os;
}

/**
 * @brief Crea una matriz de cambio de base a partir de un origen y tres vectores de base.
 * 
 * Esta función construye una matriz que transforma coordenadas desde un sistema de referencia
 * definido por el origen y los vectores u, v, w.
 * 
 * @param origin Punto de origen del nuevo sistema de coordenadas.
 * @param u Vector que define la dirección del eje x en el nuevo sistema.
 * @param v Vector que define la dirección del eje y en el nuevo sistema.
 * @param w Vector que define la dirección del eje z en el nuevo sistema.
 * @return Matriz de cambio de base.
 */
Matrix baseChange(const Coordinate& origin, const Coordinate& u, const Coordinate& v, const Coordinate& w){
    Matrix m = identity();
    m[0][3] = origin.x;
    m[1][3] = origin.y;
    m[2][3] = origin.z;
    
    m[0][0] = u.x;
    m[1][0] = u.y;
    m[2][0] = u.z;

    m[0][1] = v.x;
    m[1][1] = v.y;
    m[2][1] = v.z;

    m[0][2] = w.x;
    m[1][2] = w.y;
    m[2][2] = w.z;
    return m;
}

/**
 * @brief Multiplica una matriz por un objeto Coordinate.
 * 
 * Esta función aplica una transformación matricial a un objeto Coordinate, resultando en
 * un nuevo objeto Coordinate transformado.
 * 
 * @param m Matriz de transformación.
 * @param c Objeto Coordinate a transformar.
 * @return Nuevo objeto Coordinate resultante de la transformación.
 */
Coordinate operator*(const Matrix& m, const Coordinate& c){
    double new_x, new_y, new_z, new_w;

    new_x = m[0][0] * c.x + m[0][1] * c.y + m[0][2] * c.z + m[0][3] * c.w;
    new_y = m[1][0] * c.x + m[1][1] * c.y + m[1][2] * c.z + m[1][3] * c.w;
    new_z = m[2][0] * c.x + m[2][1] * c.y + m[2][2] * c.z + m[2][3] * c.w;
    new_w = m[3][0] * c.x + m[3][1] * c.y + m[3][2] * c.z + m[3][3] * c.w;
   
    /* normalizar
    if(c.w == 1){
        new_x = new_x / new_w; 
        new_y = new_y / new_w; 
        new_z = new_z / new_w;
        new_w = new_w / new_w; 
    }else{
        new_w = 0;
    }
    */

    return Coordinate(new_x, new_y, new_z, new_w);
}

/**
 * @brief Multiplica dos objetos Coordinate componente a componente.
 * 
 * Esta función multiplica cada componente de dos objetos Coordinate, resultando en un nuevo objeto
 * Coordinate con las componentes multiplicadas.
 * 
 * @param c1 Primer objeto Coordinate.
 * @param c2 Segundo objeto Coordinate.
 * @return Nuevo objeto Coordinate con las componentes multiplicadas.
 */
Coordinate operator*(const Coordinate& c1, const Coordinate& c2){
    return Coordinate(
        c1.x * c2.x,
        c1.y * c2.y,
        c1.z * c2.z,
        c1.w * c2.w
    );
}

/**
 * @brief Multiplica un objeto Coordinate por un escalar constante.
 * 
 * Esta función multiplica cada componente de un objeto Coordinate por un valor constante,
 * resultando en un nuevo objeto Coordinate con las componentes escaladas.
 * 
 * @param c Objeto Coordinate a multiplicar.
 * @param constant Valor constante por el cual se multiplican las componentes.
 * @return Nuevo objeto Coordinate con las componentes multiplicadas por el escalar.
 */
Coordinate operator*(const Coordinate& c, const double constant){
    return Coordinate(
        c.x * constant,
        c.y * constant,
        c.z * constant,
        c.w
    );
}

/**
 * @brief Multiplica un escalar constante por un objeto Coordinate.
 * 
 * Esta función multiplica cada componente de un objeto Coordinate por un valor constante,
 * resultando en un nuevo objeto Coordinate con las componentes escaladas.
 * 
 * @param constant Valor constante por el cual se multiplican las componentes.
 * @param c Objeto Coordinate a multiplicar.
 * @return Nuevo objeto Coordinate con las componentes multiplicadas por el escalar.
 */
Coordinate operator*(const double constant, const Coordinate& c){
    return c * constant;
}

/**
 * @brief Divide dos objetos Coordinate componente a componente.
 * 
 * Esta función divide cada componente de un objeto Coordinate por las componentes correspondientes
 * de otro objeto Coordinate, resultando en un nuevo objeto Coordinate con las componentes divididas.
 * 
 * @param c1 Primer objeto Coordinate (numerador).
 * @param c2 Segundo objeto Coordinate (denominador).
 * @return Nuevo objeto Coordinate con las componentes divididas.
 */
Coordinate operator/(const Coordinate& c1, const Coordinate& c2){
    return Coordinate(
        c1.x / c2.x,
        c1.y / c2.y,
        c1.z / c2.z,
        0.0
    );
}

/**
 * @brief Divide un objeto Coordinate por un escalar constante.
 * 
 * Esta función divide cada componente de un objeto Coordinate por un valor constante,
 * resultando en un nuevo objeto Coordinate con las componentes divididas.
 * 
 * @param c Objeto Coordinate a dividir.
 * @param constant Valor constante por el cual se dividen las componentes.
 * @return Nuevo objeto Coordinate con las componentes divididas por el escalar.
 */
Coordinate operator/(const Coordinate& c, const double constant){
    return Coordinate(
        c.x / constant,
        c.y / constant,
        c.z / constant,
        0.0
    );
}

/**
 * @brief Suma dos objetos Coordinate componente a componente.
 * 
 * Esta función suma cada componente de dos objetos Coordinate, resultando en un nuevo objeto
 * Coordinate con las componentes sumadas.
 * 
 * @param c1 Primer objeto Coordinate.
 * @param c2 Segundo objeto Coordinate.
 * @return Nuevo objeto Coordinate con las componentes sumadas.
 */
Coordinate operator+(const Coordinate& c1, const Coordinate& c2){
    return Coordinate(
        c1.x + c2.x,
        c1.y + c2.y,
        c1.z + c2.z,
        0.0
    );
}

/**
 * @brief Suma un objeto Coordinate con un escalar constante.
 * 
 * Esta función suma un valor constante a cada componente de un objeto Coordinate,
 * resultando en un nuevo objeto Coordinate con las componentes incrementadas por el escalar.
 * 
 * @param c Objeto Coordinate al que se le suma el escalar.
 * @param constant Valor constante que se suma a cada componente.
 * @return Nuevo objeto Coordinate con las componentes incrementadas por el escalar.
 */
Coordinate operator+(const Coordinate& c, const double constant){
    return Coordinate(
        c.x + constant,
        c.y + constant,
        c.z + constant,
        0.0
    );
}

/**
 * @brief Suma un escalar constante a un objeto Coordinate.
 * 
 * Esta función suma un valor constante a cada componente de un objeto Coordinate,
 * resultando en un nuevo objeto Coordinate con las componentes incrementadas por el escalar.
 * 
 * @param constant Valor constante que se suma a cada componente.
 * @param c Objeto Coordinate al que se le suma el escalar.
 * @return Nuevo objeto Coordinate con las componentes incrementadas por el escalar.
 */
Coordinate operator+(const double constant, const Coordinate& c){
    return c + constant;
}

/**
 * @brief Suma un objeto Coordinate a otro objeto Coordinate.
 * 
 * Esta función suma las componentes de dos objetos Coordinate y actualiza el objeto actual.
 * 
 * @param c Objeto Coordinate a sumar al objeto actual.
 * @return Referencia al objeto Coordinate actualizado.
 */
Coordinate& Coordinate::operator+=(const Coordinate& c){
    this->x += c.x;
    this->y += c.y;
    this->z += c.z;
    return *this;
}

/**
 * @brief Suma un escalar constante a cada componente del objeto Coordinate.
 * 
 * Esta función suma un valor constante a cada componente del objeto Coordinate y actualiza el objeto actual.
 * 
 * @param constant Valor constante que se suma a cada componente.
 * @return Referencia al objeto Coordinate actualizado.
 */
Coordinate& Coordinate::operator+=(const double constant){
    this->x += constant;
    this->y += constant;
    this->z += constant;
    return *this;
}

/**
 * @brief Divide el objeto Coordinate por un escalar constante.
 * 
 * Esta función divide cada componente del objeto Coordinate por un valor constante y actualiza el objeto actual.
 * 
 * @param constant Valor constante por el cual se dividen las componentes.
 * @return Referencia al objeto Coordinate actualizado.
 */
Coordinate& Coordinate::operator*=(const double constant){
    this->x *= constant;
    this->y *= constant;
    this->z *= constant;
    return *this;
}

/**
 * @brief Divide el objeto Coordinate por un escalar constante.
 * 
 * Esta función divide cada componente del objeto Coordinate por un valor constante y actualiza el objeto actual.
 * 
 * @param constant Valor constante por el cual se dividen las componentes.
 * @return Referencia al objeto Coordinate actualizado.
 */
Coordinate& Coordinate::operator/=(const double constant){
    this->x /= constant;
    this->y /= constant;
    this->z /= constant;
    return *this;
}

/**
 * @brief Calcula el componente máximo de un objeto Coordinate.
 * 
 * Esta función devuelve el valor máximo entre las componentes x, y, z de un objeto Coordinate.
 * 
 * @param c Objeto Coordinate del cual se calcula el componente máximo.
 * @return Valor máximo entre las componentes x, y, z.
 */
double maxComponent(const Coordinate& c){
    return std::max(c.x, std::max(c.y, c.z));
}
