#include "Plane.hpp"


Plane::~Plane(){
    this->normal.~Vector();
}

Plane::Plane(const Vector& normal, const double dist){
    this->normal = normal;
    this->dist = dist;
}
/*
Plane::Plane(const Point& p1, const Point& p2, const Point& p3){
    this->normal = normalize(crossProduct((p1-p2), (p3-p2)));
}
Plane::Plane(const Vector& t1, const Vector& t2){
    
}
Plane::Plane(const Vector& normal){
    
}
*/

bool Plane::isIntersectedBy(const Ray& ray, IntersectableFigure::Intersection& intersection) const{
    double denom = dotProduct(ray.dir, this->normal);
    if(denom == 0){
        return false;
    }
    double div = this->dist + (ray.origin * (this->normal));
    intersection.t = -(div/denom);
    intersection.normal = this->normal;
    intersection.intersectionPoint = ray.at(intersection.t);
    return intersection.t >= 0;
}


           