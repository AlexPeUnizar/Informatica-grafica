#include "Ray.hpp"

Ray::Ray(const Point& origin, const Vector& dir){
    this->origin = origin;
    this->dir = dir;
}

Ray::~Ray(){
    origin.~Point();
    dir.~Vector();
}

std::ostream& operator<<(std::ostream& os, const Ray &r){
    os << "Ray(" << "Origin: " << r.origin << "; Direcction: " << r.dir << ")";
    return os;
}

Point Ray::at(double t){
    return Point(
        this->origin.x + t*this->dir.x,
        this->origin.y + t*this->dir.y,
        this->origin.z + t*this->dir.z
    );
}

