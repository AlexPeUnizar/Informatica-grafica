#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
#include "FigureCollection.hpp"

using namespace std;

double randomDouble(double min, double max);

int main(){
    srand(time(NULL));
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
    Sphere upSphere(Point(0, 0.7, -0), 0.3);
    upSphere.setColor(3,54,1);

    FigureCollection figures(vector<Figure*>(
        {&leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, &leftSphere, &rightSphere, &upSphere}
    ));
    
    //Camera 
    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);
    size_t width = 256;
    size_t height = 256;
    Camera camera(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    camera.setHeight(height);
    camera.setWidth(width);

    PPM image(width, height);

    Vector upperLeft = cameraForwardVector + cameraLeftVector + cameraUpVector;
    Vector down = cameraUpVector * -2; 
    Vector right = cameraLeftVector * -2;

    for (size_t y = 0; y < height; y++){
        for (size_t x = 0; x < width; x++){
            #if 0
            Ray ray = Ray(
                camera.getO(),
                normalize(
                    upperLeft + 
                    right * (double(x)/double(camera.getWidth())) + 
                    down * (double(y)/double(camera.getHeight()))
                )
            );

            
            Figure *closestFig = nullptr;
            IntersectableFigure::Intersection intersection;
            double min = INT_MAX-1;
            
            for(auto fig: figures){
                if(fig->isIntersectedBy(ray, intersection)){
                    if(intersection.t < min){
                        closestFig = fig;
                        min = intersection.t;
                    }
                }
            }
            
            double r, g, b;
            r = closestFig->getR();
            g = closestFig->getG();
            b = closestFig->getB();
                
            image[y][x] = std::make_shared<PPM::Pixel>(PPM::Pixel{r/255, g/255, b/255});
            #else
                Vector vectorToUpperCorner =  upperLeft + 
                                        right * (double(x)/double(camera.getWidth())) + 
                                        down * (double(y)/double(camera.getHeight()));
                Vector vectorToLowerCorner =  upperLeft + 
                                        right * (double(x+1)/double(camera.getWidth())) + 
                                        down * (double(y+1)/double(camera.getHeight()));
                Point upCorner = Ray(camera.getO(), normalize(vectorToUpperCorner)).at(module(vectorToUpperCorner));
                Point downCorner = Ray(camera.getO(), normalize(vectorToLowerCorner)).at(module(vectorToLowerCorner));

                Point p1 = Point(randomDouble(upCorner.x, downCorner.x), randomDouble(downCorner.y, upCorner.y), upCorner.z);
                Point p2 = Point(randomDouble(upCorner.x, downCorner.x), randomDouble(downCorner.y, upCorner.y), upCorner.z);
                Point p3 = Point(randomDouble(upCorner.x, downCorner.x), randomDouble(downCorner.y, upCorner.y), upCorner.z);
                Point p4 = Point(randomDouble(upCorner.x, downCorner.x), randomDouble(downCorner.y, upCorner.y), upCorner.z);

                vector<Ray> rays = vector<Ray>({
                    Ray(camera.getO(), p1 - camera.getO()),
                    Ray(camera.getO(), p2 - camera.getO()),
                    Ray(camera.getO(), p3 - camera.getO()),
                    Ray(camera.getO(), p4 - camera.getO()),
                });

                double r=0, g=0, b=0;

                for(auto ray: rays){
                    Figure *closestFig = nullptr;
                    double min = INT_MAX-1;
                    IntersectableFigure::Intersection intersection = IntersectableFigure::Intersection();

                    for(auto fig:figures){
                        if(fig->isIntersectedBy(ray,intersection)){
                            if(intersection.t < min){
                                closestFig = fig;
                                min = intersection.t;
                            }
                        }
                    }
                    r += closestFig->getR();
                    g += closestFig->getG();
                    b += closestFig->getB();
                }
                
                    
                image[y][x] = std::make_shared<PPM::Pixel>(PPM::Pixel{
                    (r/4.0)/255.0, 
                    (g/4.0)/255.0, 
                    (b/4.0)/255.0
                });

            #endif

        }
    }

    image.save();
    return 0;
}   

double randomDouble(double min, double max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

