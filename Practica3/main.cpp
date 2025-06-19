/**
 * @file main.cpp
 * @brief Punto de entrada principal para la aplicación de renderizado Path Tracing.
 *
 * Este programa configura una escena 3D sencilla con planos y esferas, define materiales,
 * una fuente de luz y renderiza la escena usando un algoritmo de path tracing.
 * La imagen renderizada se guarda en formato PPM y se abre automáticamente con GIMP.
 *
 * Dependencias:
 * - PathTracing.hpp y clases relacionadas de escena, materiales y geometría.
 *
 * @author Alex
 * @date 18-6-2025
 */
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

    Sphere leftSphere(
        Point(-0.5, -0.7, 0.25),
        0.3,
        std::make_shared<Material>(
            Color(0.0, 0.7, 0.7),  // kd: Azul
            Color(0.3, 0.3, 0.3),  // ks: Moderada reflectividad
            Color(0.0, 0.0, 0.0),  // kt: Sin refracción
            1.0                    // ior
        )
    );

    
    Sphere rightSphere(
        Point(0.5, -0.7, -0.25),
        0.3,
        std::make_shared<Material>(
            Color(0, 0.0, 0),  // kd: Sin difusa
            Color(0.1, 0.1, 0.1),  // ks: Baja reflectividad
            Color(0.9, 0.9, 0.9),  // kt: Alta transparencia
            1.5                    // ior (índice de refracción)
        )
    );


    // Integración en el FigureCollection
    FigureCollection figures(vector<Figure*>(
        {
            &leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, 
            &leftSphere, &rightSphere
        }
    ));


    /* LIGHTS */
    Light light(Point(0, 0.5, 0), Color(1, 1 ,1));
    //Light light2(Point(0, 05, 0), Color(1,0,1));
    vector<shared_ptr<Light>> lights = vector<shared_ptr<Light>>({
        make_shared<Light>(light)
    });
    //Camera 

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);
    size_t width = IMAGE_WIDTH;
    size_t height = IMAGE_WIDTH;
    Camera camera(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    camera.setHeight(height);
    camera.setWidth(width);
    
    PPM image;
    {
        ScopedTimer timer("Render Timer");
        image = camera.render(figures, lights);
    }

    gammaAndClamping(image, 2.2, 1);
    image.save();
    
    cout << "Done." << endl;
    try{
        system("\"C:/Program Files/GIMP 3/bin/gimp-3.0.exe\" out.ppm");
    }catch(const std::exception& e){
        cerr << "Error opening GIMP: " << e.what() << endl;
    }
    return 0;
}   

