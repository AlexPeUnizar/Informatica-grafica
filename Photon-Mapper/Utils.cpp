#define _USE_MATH_DEFINES
#include "Utils.hpp"
#include <cstdlib>
#include <time.h>
#include <math.h>

double randomDouble(double min, double max){
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

double randomDouble(){
    return randomDouble(0.0, 1.0);
}

Vector randomDirection(){
    double theta = 2 * M_PI * randomDouble(0, 1); 
    double phi = acos(2 * randomDouble(0, 1) - 1);
    return Vector(
        sin(phi) * cos(theta),
        sin(phi) * sin(theta),
        cos(phi)
    );
}

Vector randomDirection(const Point& point, const Vector& normal){
    Vector random;
    double phi = 2 * M_PI * randomDouble(0, 1);
    double theta = asin(sqrt(randomDouble(0, 1)));

    random = Vector(
        sin(theta) * cos(phi),
        sin(theta) * sin(phi),
        cos(theta)
    );
    Vector randomBaseVector(0,1,0);
    double alpha = angle(normal, randomBaseVector);
    if (std::abs(alpha - M_PI) < 1e-6 || std::abs(alpha) < 1e-6) {
        randomBaseVector = Vector(1, 0, 0);
    }   
    Vector T = normalize(crossProduct(normal, randomBaseVector));
    Vector B = normalize(crossProduct(normal, T));

    Vector randomVector = baseChange(
        point,
        T,
        B,
        normal
    ) * random;

    return randomVector;
}