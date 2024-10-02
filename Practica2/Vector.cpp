#include "Vector.hpp"
#include <cmath>

Vector::~Vector(){
    
}

std::ostream& operator<<(std::ostream& os, const Vector &v){
    os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::shared_ptr<Vector> operator+(const Vector &v1, const Vector &v2){
    return std::make_shared<Vector>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

std::shared_ptr<Vector> operator-(const Vector &v1, const Vector &v2){
    return std::make_shared<Vector>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

std::shared_ptr<Vector> crossProduct(const Vector &v1, const Vector &v2){
    return std::make_shared<Vector>((v1.y * v2.z - v1.z * v2.y),
                      (v1.z * v2.x - v1.x * v2.z),
                      (v1.x * v2.y - v1.y * v2.x));
}

int32_t dotProduct(const Vector &v1, const Vector &v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

std::shared_ptr<Vector> operator*(const Vector &v, const int32_t s){
    return std::make_shared<Vector>(v.x * s, v.y * s, v.z * s);
}

std::shared_ptr<Vector> operator*(const int32_t s, const Vector &v){
    return v*s;
}

std::shared_ptr<Vector> operator/(const Vector &v, const double s){
    return std::make_shared<Vector>(v.x / s, v.y / s, v.z / s);
}

double module(const Vector &v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double angle(const Vector &v1, const Vector &v2){
    return acos((dotProduct(v1,v2))/(module(v1)*module(v2)));
}

std::shared_ptr<Vector> normalize(const Vector &v){
    return v/module(v);
}


