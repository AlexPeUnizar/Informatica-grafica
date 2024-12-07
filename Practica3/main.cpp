#include "PathTracing.hpp"
#include <iostream>

using namespace std;

int main(){
    srand(time(NULL));
    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> up(-)-down(+)
        z -> front(-)-back(+)
    */
    Color gris = Color::fromRGB(211,211,211);
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(gris));

    Sphere leftSphere(Point(-0.5, -0.7, 0.25), 0.3, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,255)));
    Sphere rightSphere(Point(0.5, -0.7, -0.25), 0.3, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,255)));
    Cylinder middleCylinder(Point(0, 0, 0.7), Vector(0, -0, -1), 0.3, 0.5, std::make_shared<Materials::Lambertian>(Color::fromRGB(102, 51, 0)));

    FigureCollection figures(vector<Figure*>(
        {&leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, &leftSphere, &rightSphere, &middleCylinder}
    ));

    /* LIGHTS */
    Light light(Point(0, 0.5, 0), Color(1,1,1));
    vector<shared_ptr<Light>> lights = vector<shared_ptr<Light>>({
        make_shared<Light>(light)
    });
    //Camera 

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);
    size_t width = 512;
    size_t height = 512;
    Camera camera(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    camera.setHeight(height);
    camera.setWidth(width);
    
    //middleCylinder.setVisible(false);
    PPM image = camera.render(figures, lights);
    gammaAndClamping(image, 2.2, 1);
    image.save();

    cout << "Done." << endl;
    return 0;
}   

