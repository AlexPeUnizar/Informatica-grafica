#include "Figure.hpp"

Figure::Figure(const std::shared_ptr<Material>& material){
    this->material = material;
}

void Figure::setColor(double r, double g, double b){
    this->material.get()->setColor(Color(r, g, b));
}

void Figure::setVisible(bool visible){
    this->visible = visible;
}

void Figure::setMaterial(const std::shared_ptr<Material>& material){
    this->material = material;
}

/**
 * @brief Establece la emision de la figura.
 * 
 * Asigna un nuevo color de emision al material de la figura.
 * 
 * @param emission Color que representa la emision de la figura.
 */
void Figure::setEmission(Color emission){
    this->material.get()->setEmission(emission);
}