#include "Color.hpp"


Color::~Color(){

}

Color& Color::operator=(const Color& c){
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
    return *this;
}

