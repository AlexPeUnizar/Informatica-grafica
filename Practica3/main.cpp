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
#include "Plane.hpp"
#include "Camera.hpp"
#include "PPM.hpp"
//#include "IntersectableCollection.hpp"

using namespace std;

int main(){
    #if 0
        Point sphereCenter(0,0,0);
        Point vecCenter(0,0,5);

        Vector rayDir = (*(Point(0,0,-5)-Point(0,0,5)));

        Sphere s(sphereCenter, 2.5);
        Ray r(vecCenter, rayDir);
        Plane p(*normalize(*(Point(0,0,5)-Point(0,0,-5))), 5);
        normalize(rayDir);

        cout << sphereCenter << std::endl;
        cout << vecCenter << std::endl;
        cout << rayDir << std::endl;

        if(p.isIntersectedBy(r)){
            cout << "Si" <<endl;
        }else{
            cout << "No" <<endl;
        }

    #else
        /*
        Planes defined by normal (n) and distance (d)
            Left plane n = (1, 0, 0), d = 1
            Right plane n = (-1, 0, 0), d = 1
            Floor plane n = (0, 1, 0), d = 1
            Ceiling plane n = (0, -1, 0), d = 1
            Back plane n = (0, 0, -1), d = 1
        Spheres defined by center (c) and radius (r) 
            Left sphere c = (-0.5, -0.7, 0.25), r = 0.3
            Right sphere c = (0.5, -0.7, -0.25), r = 0.3
        Camera and image plane defined by
            Origin O = (0, 0, -3.5)
            Left L = (-1, 0, 0)
            Up U = (0, 1, 0)
            Forward F = (0, 0, 3)
            Size 256x256 pixels
        */

        Plane leftPlane(Vector(1, 0, 0), 1);
        leftPlane.setColor(255,0,0);
        Plane rightPlane(Vector(-1, 0, 0), 1);
        rightPlane.setColor(0,255,0);
        Plane floorPlane(Vector(0, 1, 0), 1);
        floorPlane.setColor(211,211,211);
        Plane ceilingPlane(Vector(0, -1, 0), 1);
        ceilingPlane.setColor(211,211,211);
        Plane backPlane(Vector(0, 0, -1), 1);
        backPlane.setColor(211,211,211);

        Sphere leftSphere(Point(-0.5, -0.7, 0.25), 0.3);
        leftSphere.setColor(255,0,255);
        Sphere rightSphere(Point(0.5, -0.7, -0.25), 0.3);
        rightSphere.setColor(0,255,255);

        //Camera 
        Point cameraOrigin(0,0, -3.5);
        Vector cameraLeftVector(-1, 0, 0);
        Vector cameraUpVector(0, 1, 0);
        Vector cameraForwardVector(0, 0, 3);
        size_t width = 256;
        size_t height = 256;
        Camera cam(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);

        PPM imagen(width,height);

        

        
    #endif

}