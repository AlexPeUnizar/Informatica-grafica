#include "PathTracing.hpp"
#include <iostream>

using namespace std;

int main(){
    srand(time(NULL));
  
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(Color(211,211,211)));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(Color(211,211,211)));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(Color(211,211,211)));

    Sphere leftSphere(Point(-0.5, -0.7, 0.25), 0.3, std::make_shared<Materials::Lambertian>(Color(255,0,255)));
    Sphere rightSphere(Point(0.5, -0.7, -0.25), 0.3, std::make_shared<Materials::Lambertian>(Color(0,255,255)));
    Sphere upSphere(Point(0, -0.5, -0), 0.3, std::make_shared<Materials::Lambertian>(Color(3,54,1)));

    FigureCollection figures(vector<Figure*>(
        {&leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, &leftSphere, &rightSphere, &upSphere}
    ));

    Light light(Point(0, 0.5, 0), Color(1, 1, 1));
    vector<shared_ptr<Light>> lights = vector<shared_ptr<Light>>({
        make_shared<Light>(light)
    });
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
    
    upSphere.setVisible(false);

    PPM image = camera.render(figures, lights);
    gammaAndClamping(image, 0.5, 1);
    image.save();

    cout << "Done." << endl;
    return 0;
}   

