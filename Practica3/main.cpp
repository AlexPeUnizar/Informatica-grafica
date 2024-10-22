#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include "Vector.hpp"
#include "Point.hpp"
#include "Coordinate.hpp"
#include "Matrix.hpp"
#include "Figure.hpp"
#include "Sphere.hpp"

using namespace std;

int main(){
    Point sphereCenter(0,0,0);
    Point vecCenter(0,0,5);

    Vector rayDir = (*(Point(0,0,-5)-Point(0,0,5)));

    Sphere s(sphereCenter, 2.5);
    Ray r(vecCenter, rayDir);

    cout << sphereCenter << std::endl;
    cout << vecCenter << std::endl;
    cout << rayDir << std::endl;

    if(s.isIntersectedBy(r)){
        cout << "Si" <<endl;
    }else{
        cout << "No" <<endl;
    }
}