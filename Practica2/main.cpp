#include <iostream>
#include <memory>
#include <cmath>
#include "Vector.hpp"
#include "Point.hpp"
#include "Coordinate.hpp"
#include "Matrix.hpp"
using namespace std;

int main(){
    Point p1 = Point(1, 2, 3);
    Point p2 = Point(2,4,5);
    Vector v1 = Vector(1,0,0);
    Vector v2 = Vector(0,2,0);
    
    Matrix m1 = (*(*(*traslation(4,5,2) * *scale(3,4,5)) * *rotationX(M_PI)));

    cout << *(m1 * p1) << endl;

    cout << (Coordinate)p1 <<endl;
    cout << p2 <<endl;
    cout << v1 << endl;
    cout << *(2+p1) <<endl;
    cout << *(p1+2) <<endl;
    cout << *normalize(v2) << endl;

}