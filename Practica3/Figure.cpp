/**
 * @file Figure.cpp
 * @brief Implementación de la clase Figure para la gestión de figuras gráficas y sus materiales.
 * 
 * Este archivo contiene las definiciones de los métodos de la clase Figure, 
 * permitiendo la manipulación de materiales, colores y visibilidad de las figuras.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "Figure.hpp"

/**
 * @brief Constructor de la clase Figure
 * 
 * Crea un nuevo objeto Figure con el material proporcionado.
 * 
 * @param material Puntero compartido al material que se asignará a la figura.
 */
Figure::Figure(const std::shared_ptr<Material>& material){
    this->material = material;
}

/**
 * @brief Establece el color de la figura.
 * 
 * Asigna un nuevo color al material de la figura utilizando los valores RGB proporcionados.
 * 
 * @param r Componente roja del color (0.0 a 1.0).
 * @param g Componente verde del color (0.0 a 1.0).
 * @param b Componente azul del color (0.0 a 1.0).
 */
void Figure::setColor(double r, double g, double b){
    this->material.get()->setColor(Color(r, g, b));
}

/**
 * @brief Establece la visibilidad de la figura.
 * 
 * Cambia el estado de visibilidad de la figura, permitiendo que sea renderizada o no.
 * 
 * @param visible Valor booleano que indica si la figura es visible (true) o no (false).
 */
void Figure::setVisible(bool visible){
    this->visible = visible;
}

/**
 * @brief Establece el material de la figura.
 * 
 * Asigna un nuevo material a la figura, permitiendo cambiar sus propiedades visuales.
 * 
 * @param material Puntero compartido al nuevo material que se asignará a la figura.
 */
void Figure::setMaterial(const std::shared_ptr<Material>& material){
    this->material = material;
}
