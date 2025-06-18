/**
 * @file Color.cpp
 * @brief Implementación de los métodos de la clase Color.
 * @author Alex
 * @date 18-6-2025
 */
#include "Color.hpp"

/**
 * @brief Destructor de la clase Color.
 * 
 */
Color::~Color(){

}

/**
 * @brief Constructor de copia de la clase Color.
 * 
 * Crea un nuevo objeto Color copiando los valores de otro objeto Color existente.
 * 
 * @param c Objeto Color a copiar.
 */
Color& Color::operator=(const Color& c){
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
    return *this;
}

/**
 * @brief Operador de salida sobrecargado para la clase Color.
 * 
 * Esta función permite imprimir el objeto Color en un formato legible.
 * 
 * @param os Flujo de salida donde escribir.
 * @param c Objeto Color que se va a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Color &c){
    os << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}

/**
 * @brief Crea un objeto Color a partir de valores RGB.
 * 
 * Este método estático convierte valores RGB (0-255) en un objeto Color con valores normalizados (0.0-1.0).
 * 
 * @param r_ Componente rojo (0-255).
 * @param g_ Componente verde (0-255).
 * @param b_ Componente azul (0-255).
 * @return Color Un objeto Color con valores RGB normalizados.
 */
Color Color::fromRGB(double r_, double g_, double b_){
    return Color(r_ / 255.0, g_ / 255.0, b_ / 255.0);
}