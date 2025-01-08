#include "Vector.hpp"
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Vector &v){
    os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

Vector operator+(const Vector &v1, const Vector &v2){
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector &v1, const Vector &v2){
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector crossProduct(const Vector &v1, const Vector &v2){
    return Vector((v1.y * v2.z - v1.z * v2.y),
                      (v1.z * v2.x - v1.x * v2.z),
                      (v1.x * v2.y - v1.y * v2.x));
}

double dotProduct(const Vector &v1, const Vector &v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector operator*(const Vector &v, const double s){
    return Vector(v.x * s, v.y * s, v.z * s);
}

Vector operator*(const double s, const Vector &v){
    return v*s;
}

Vector operator/(const Vector &v, const double s){
    return Vector(v.x / s, v.y / s, v.z / s);
}

double module(const Vector &v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double angle(const Vector &v1, const Vector &v2){
    return acos((dotProduct(v1,v2))/(module(v1)*module(v2)));
}

Vector normalize(const Vector &v){
    return v/module(v);
}

Vector reflect(const Vector& incident, const Vector& normal) {
    return incident - 2.0f * dotProduct(incident, normal) * normal;
}

Vector refract(const Vector& incident, const Vector& normal, double ior_ratio) {
    double cosi = dotProduct(incident, normal);
    double etai = 1;
    double etat = ior_ratio;
    if (cosi > 0){
        std::swap(etai, etat);
    } 
    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0){
        return Vector(0, 0, 0);  // Total internal reflexion
    }
    return eta * incident + (eta * cosi - sqrt(k)) * normal;
}

Vector operator-(const Vector& v){
    return Vector(-v.x, -v.y, -v.z);
}
