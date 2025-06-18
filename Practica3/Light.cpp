/**
 * @file Light.cpp
 * @brief Implementación de la clase Light para la gestión de fuentes de luz en la escena.
 * 
 * Este archivo contiene la definición de los métodos de la clase Light, que representa una fuente de luz
 * con una posición y una potencia de color en el espacio 3D.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Light.hpp"

/** 
 * @brief Constructor de la clase Light.
 * 
 * Crea una nueva fuente de luz con un centro y una potencia especificados.
 * 
 * @param center Punto que representa el centro de la luz.
 * @param power Color que representa la potencia de la luz.
 */
Light::Light(const Point& center, const Color& power){
    this->center = center;
    this->power = power;    
}

/**
 * @brief Constructor por defecto de la clase Light.
 * 
 * Inicializa una fuente de luz con un centro en el origen (0,0,0) y potencia blanca (1,1,1).
 */
Light::Light(){
    this->center = Point(0,0,0);
    this->power = Color(1,1,1);
}

/**
 * @brief Destructor de la clase Light.
 * 
 * Libera los recursos asociados con la fuente de luz, incluyendo el centro y la potencia.
 */
Light::~Light(){
    this->center.~Point();
    this->power.~Color();
}

/**
 * @brief Obtiene el centro de la fuente de luz.
 * 
 * Este método devuelve el punto que representa el centro de la luz.
 * 
 * @return Punto que representa el centro de la luz.
 */
Point Light::getCenter() const{
    return this->center;
}

/**
 * @brief Obtiene la potencia de la fuente de luz.
 * 
 * Este método devuelve el color que representa la potencia de la luz.
 * 
 * @return Color que representa la potencia de la luz.
 */
Color Light::getPower() const{
    return this->power;
}
