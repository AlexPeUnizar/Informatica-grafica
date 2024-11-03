#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Point &origin, double r, const std::shared_ptr<Material>& material): Figure(material){
    this->origin = origin;
    this->r = r;
}

Sphere::~Sphere(){
    origin.~Point();
}

bool Sphere::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const{
    if(!this->visible){
        return false;
    }
    Vector vectorToCenter = ray.origin - this->origin;
    double a = dotProduct(ray.dir, ray.dir);
    double b = 2 * dotProduct(vectorToCenter, ray.dir);
    double c = dotProduct(vectorToCenter, vectorToCenter) - this->r * this->r;
    //std::cout << "a: " << a << "; b: " << b << "; c: " << c << std::endl;
    double delta = b*b - 4 * a * c;
    //std::cout << "delta: " << delta << std::endl;

    if(delta < 0){
        return false;
    }
    
    double t0 = (-b - sqrt(delta)) / (2 * a);
    if(t0 < tMax && t0 > tMin){
        intersection.t = t0;
        intersection.intersectionPoint = ray.at(intersection.t);
        intersection.normal = normalize(intersection.intersectionPoint - this->origin);
        intersection.material = this->material;
        return true;
    }
    
    double t1 = (-b + sqrt(delta)) / (2 * a);
    if(t1 < tMax && t1 > tMin){
        intersection.t = t1;
        intersection.intersectionPoint = ray.at(intersection.t);
        intersection.normal = normalize(intersection.intersectionPoint - this->origin);
        intersection.material = this->material;
        return true;
    }
    return false;
    /*
    if(t0 < 0 && t1 < 0){
        return false;
    }
    
    intersection.t = (t0 > 0 && t1 > 0) ? std::min(t0, t1) : (t0 > 0 ? t0 : (t1 > 0 ? t1 : -1));
    intersection.intersectionPoint = ray.at(intersection.t);
    intersection.normal = normalize(intersection.intersectionPoint - this->origin);
    intersection.material = this->material;

    //std::cout << "t0: " << t0 << "; t1: " << t1 << std::endl;
    return (intersection.t >= tMin && intersection.t <= tMax);
    */
}
