#include "Ray.hpp"

Ray::Ray(const Point& o, const Vector& d){
    this->o = o;
    this->d = d;
}

Ray::~Ray(){
    o.~Point();
    d.~Vector();
}

