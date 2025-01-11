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
