#include "Figure.hpp"

void Figure::setColor(double r,double g, double b){
    this->color = Color{r,g,b};
}

double Figure::getR(){
    return this->color.r;
}
double Figure::getG(){
    return this->color.g;
}
double Figure::getB(){
    return this->color.b;
}
