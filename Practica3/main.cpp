#include "PathTracing.hpp"
#include <iostream>

using namespace std;

int main(){
    srand(time(NULL));
    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> down(-)-up(+)
        z -> front(-)-back(+)
    */
    Color gris = Color::fromRGB(211,211,211);
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(gris));

    Sphere leftSphere(Point(-0.5, -0.7, 0.25), 0.3, std::make_shared<Material>(Color(0.0, 0.0, 1.0),  // Color azul para difuso (kd)
                                     Color(0.5, 0.5, 1.0),  // Color azul claro para especular (ks)
                                     Color(0.0, 0.0, 0.0),  // Sin componente refractiva (kt)
                                     1.5));
    Sphere rightSphere(Point(0.5, -0.7, -0.25), 0.3, std::make_shared<Material>(Color::fromRGB(255,255,255), Color(0.6,0.6,0.6),  Color(0.4,0.4,0.4), 1.5));
    /*
    vector<shared_ptr<Point>> vertices = {
        make_shared<Point>(0-0.5, 0-0.5, 0),      // Base inferior izquierda
        make_shared<Point>(1-0.5, 0-0.5, 0),      // Base inferior derecha
        make_shared<Point>(0.5-0.5, 0-0.5, 1),    // Base superior
        make_shared<Point>(0.5-0.5, 1-0.5, 0.5)   // Pico de la pirámide
    };

    vector<int> indices = {
        0, 1, 2, // Base
        0, 1, 3, // Cara 1
        1, 2, 3, // Cara 2
        2, 0, 3  // Cara 3
    };

    auto material = std::make_shared<Materials::Lambertian>(Color::fromRGB(255,255,0));
    TriangleMesh pyramidMesh(vertices, indices, material);
    */
    
    FigureCollection figures(vector<Figure*>(
        {&leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, &leftSphere, &rightSphere}
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
    
    //triangle.setVisible(false);
    //leftSphere.setVisible(false);
    //rightSphere.setVisible(false);
    PPM image;
    
    {
        ScopedTimer timer("Render Timer");
        image = camera.render(figures, lights);
    }

    gammaAndClamping(image, 2.2, 1);
    image.save();
    
    cout << "Done." << endl;
    
    return 0;
}   

