#include "Plane.hpp"


Plane::~Plane(){
}

Plane::Plane(const Vector& normal, const Point& origin){
    
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


         