#include "Light.hpp"

Light::Light(Point center, Color Power){
    this->center = center;
    this->power = power;    
}

Light::Light(){
    this->center = Point(0,0,0);
    this->power = Color(1,1,1);
}

Light::~Light(){
    this->center.~Point();
    this->power.~Color();
}
