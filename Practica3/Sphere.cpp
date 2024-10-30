#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Point &origin, double r){
    this->origin = origin;
    this->r = r;
}

Sphere::~Sphere(){
    origin.~Point();
}

bool Sphere::isIntersectedBy(const Ray& ray, Intersection& intersection) const{
    if(!this->visible){
        return false;
    }
    double a = pow(module(ray.dir), 2); 
    double b = 2 * dotProduct(ray.dir, (ray.origin - this->origin));
    double c = pow(module((ray.origin-this->origin)), 2) - pow(this->r, 2);
    //std::cout << "a: " << a << "; b: " << b << "; c: " << c << std::endl;
    double delta = pow(b, 2) - 4 * a * c;
    //std::cout << "delta: " << delta << std::endl;

    if(delta < 0 || a == 0){
        return false;
    }
    
    double t0 = (-b + sqrt(delta)) / (2 * a);
    double t1 = (-b - sqrt(delta)) / (2 * a);
    if(t0 < 0 && t1 < 0){
        return false;
    }
    
    intersection.t = (t0 > 0 && t1 > 0) ? std::min(t0, t1) : (t0 > 0 ? t0 : (t1 > 0 ? t1 : -1));
    intersection.intersectionPoint = ray.at(intersection.t);
    intersection.normal = normalize(intersection.intersectionPoint - this->origin);
    intersection.color = Color(color.r, color.g, color.b);

    //std::cout << "t0: " << t0 << "; t1: " << t1 << std::endl;
    return true;
}
