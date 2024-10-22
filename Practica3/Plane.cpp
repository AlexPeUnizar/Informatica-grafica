#include "Plane.hpp"


Plane::~Plane(){
    this->normal.~Vector();
    this->p.~Point();
}

Plane::Plane(const Vector& normal, const Point& origin){
    this->normal = normal;
    this->p = origin;
}
Plane::Plane(const Point& p1, const Point& p2, const Point& p3){
    
}
Plane::Plane(const Vector& t1, const Vector& t2){
    
}
Plane::Plane(const Vector& normal){
    
}

bool Plane::isIntersectedBy(const Ray& ray) const{
    double denom = dotProduct(ray.dir, this->normal);
    if(denom == 0){
        return false;
    }
    double div = dotProduct(*(this->p - ray.origin), this->normal);
    return (div/denom) >= 0;
}


         