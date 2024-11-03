#include "Light.hpp"

Light::Light(const Point& center, const Color& power){
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

Point Light::getCenter() const{
    return this->center;
}

Color Light::getPower() const{
    return this->power;
}

