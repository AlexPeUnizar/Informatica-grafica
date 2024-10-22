#include "Ray.hpp"

Ray::Ray(const Point& origin, const Vector& dir){
    this->origin = origin;
    this->dir = dir;
}

Ray::~Ray(){
    origin.~Point();
    dir.~Vector();
}


