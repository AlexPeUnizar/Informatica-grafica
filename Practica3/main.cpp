#include "PathTracing.hpp"

using namespace std;

int main(){
    srand(time(NULL));

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
    Sphere upSphere(Point(0, -0.5, -0), 0.3);
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
    
    PPM image = camera.render(figures);

    image.save();
    cout << "Done." << endl;
    return 0;
}   

