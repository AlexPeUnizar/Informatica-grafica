#include "Color.hpp"


Color::~Color(){

}

Color& Color::operator=(const Color& c){
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Color &c){
    os << "Color(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}

Color Color::fromRGB(double r_, double g_, double b_){
    return Color(r_ / 255.0, g_ / 255.0, b_ / 255.0);
}