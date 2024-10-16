#include "Sphere.hpp"

Sphere::Sphere(const Point &o, double r){
    this->o = o;
    this->r = r;
}

Sphere::~Sphere(){
    o.~Point();
}

bool intersect(){

}