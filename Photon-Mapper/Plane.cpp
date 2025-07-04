#include "Plane.hpp"


Plane::~Plane(){
    this->normal.~Vector();
}

Plane::Plane(const Vector& normal, const double dist, const std::shared_ptr<Material>& material): Figure(material){
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

bool Plane::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const{
    if(!this->visible){
        return false;
    }

    double denom = dotProduct(ray.dir, this->normal);
    if(denom == 0){
        return false;
    }
    double div = this->dist + (ray.origin * (this->normal));
    
    intersection.t = -(div/denom);
    intersection.normal = this->normal;
    intersection.intersectionPoint = ray.at(intersection.t);
    intersection.material = this->material;
    intersection.figureName = typeid(this).name();


    return (intersection.t >= 0 && intersection.t > tMin && intersection.t < tMax);
}

void Plane::applyTransform(const Matrix& m) {
    // Elegir un punto sobre el plano
    Point pointOnPlane = Point(normal * -dist); // punto p tal que n·p + d = 0

    // Transformar ese punto
    Point newPoint = m * pointOnPlane;

    // Transformar la normal usando el inverso transpuesto (solo válido si m es afín)
    Matrix inverseTransposed = transpose(inverse(m));
    Vector newNormal = normalize(Vector(inverseTransposed * normal));

    // Recalcular la nueva distancia al origen
    dist = -dotProduct(newNormal, newPoint);
    normal = newNormal;
}
