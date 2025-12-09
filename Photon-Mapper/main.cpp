#define _USE_MATH_DEFINES
#include "PathTracing.hpp"
#include <iostream>
#include <math.h>

using namespace std;

void parseArgs(int argc, char* argv[]);

int main(int argc, char* argv[]){
    parseArgs(argc, argv);

    srand(time(NULL));
    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> down(-)-up(+)
        z -> front(-)-back(+)
    */
    Color gris = Color::fromRGB(211,211,211);

    //auto p1 = std::make_shared<Point>(-1, -1, -1);
    //auto p2 = std::make_shared<Point>(1, -1, -1);
    //auto p3 = std::make_shared<Point>(1, -1, 1);
    //auto p4 = std::make_shared<Point>(-1, -1, 1);
//
    //std::vector<int> indices = {
    //    0, 1, 2, // triángulo 1
    //    0, 2, 3  // triángulo 2
    //};
//
    //std::vector<std::shared_ptr<Point>> vertices = {p1, p2, p3, p4};
//
    //auto grayMaterial = std::make_shared<Material>(gris);
    //
    //TriangleMesh floorPlaneMesh(vertices, indices, grayMaterial);
    //
    //TriangleMesh ceilingPlaneMesh(vertices, indices, grayMaterial);
    //ceilingPlaneMesh.applyTransform(translation(0, 2, 0));  // y = -1 → y = 1
    //ceilingPlaneMesh.applyTransform(scale(1, -1, 1));        // Voltea normal hacia abajo
//
    //// Pared izquierda (x = -1)
    //TriangleMesh leftPlaneMesh(vertices, indices, std::make_shared<Material>(Color::fromRGB(255,0,0)));
    //leftPlaneMesh.applyTransform(rotationZ(- M_PI / 2));      // Plano vertical YZ
    //leftPlaneMesh.applyTransform(translation(-1, 0, 0));     // x = -1
//
    //// Pared derecha (x = 1)
    //TriangleMesh rightPlaneMesh(vertices, indices, std::make_shared<Material>(Color::fromRGB(0,255,0)));
    //rightPlaneMesh.applyTransform(rotationZ(M_PI / 2));      // Plano vertical YZ
    //rightPlaneMesh.applyTransform(translation(1, 0, 0));     // x = 1
//
    //// Pared de fondo (z = 1)
    //TriangleMesh backPlaneMesh(vertices, indices, grayMaterial);
    //backPlaneMesh.applyTransform(rotationX(M_PI / 2));       // Plano vertical XY
    //backPlaneMesh.applyTransform(translation(0, 0, 1));      // z = 1

    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Material>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Material>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Material>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Material>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Material>(gris));
        
            
    /*
    Sphere leftSphere(Point(-0.5, -0.7, 0.25), 0.3, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,255)));
    Sphere rightSphere(Point(0.5, -0.7, -0.25), 0.3, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,255)));
    */
   /*
    Sphere leftSphere(
        Point(-0.5, -0.7, 0.25),
        0.3,
        std::make_shared<Material>(
            Color::fromRGB(255,0,255),  // kd: Azul
            Color(0, 0, 0),  // ks: Moderada reflectividad
            Color(0.0, 0.0, 0.0),  // kt: Sin refracción
            1.0                    // ior
        )
    );

    
    Sphere rightSphere(
        Point(0.5, -0.7, -0.25),
        0.3,
        std::make_shared<Material>(
            Color::fromRGB(0,255,255),  // kd: Sin difusa
            Color(0, 0, 0),  // ks: Baja reflectividad
            Color(0, 0, 0),  // kt: Alta transparencia
            1.5                    // ior (índice de refracción)
        )
    );
*/
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
            Color(0.0, 0.0, 0.0),  // kd: Sin difusa
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
 // Define materials
    auto triangleMaterial = std::make_shared<Material>(
        Color(0.0, 0.0, 0.0),  // kd: Sin difusa
        Color(0.1, 0.1, 0.1),  // ks: Baja reflectividad
        Color(0.9, 0.9, 0.9),  // kt: Alta transparencia
        1.5                    // ior (índice de refracción)
    );
 
 // Define vertices of the triangle
    Point v1(0, -0.5, 0.5);  // Bottom vertex
    Point v2(-0.5, 0.366, 0.5); // Top-left vertex
    Point v3(0.5, 0.366, 0.5);  // Top-right vertex

    // Spheres at triangle vertices (thicker)
    Sphere sphere1(v1, 0.15, triangleMaterial);
    Sphere sphere2(v2, 0.15, triangleMaterial);
    Sphere sphere3(v3, 0.15, triangleMaterial);

    // Cylinders forming triangle edges (thicker and do not touch spheres)
    double gap = 0.15; // Gap between spheres and cylinders
    Cylinder cylinder1(v1 + (Coordinate)(normalize(v2 - v1) * gap), normalize(v2 - v1), 0.1, 1.0 - 2 * gap, triangleMaterial);
    Cylinder cylinder2(v2 + (Coordinate)(normalize(v3 - v2) * gap), normalize(v3 - v2), 0.1, 1.0 - 2 * gap, triangleMaterial);
    Cylinder cylinder3(v3 + (Coordinate)(normalize(v1 - v3) * gap), normalize(v1 - v3), 0.1, 1.0 - 2 * gap, triangleMaterial);

    // FigureCollection
    FigureCollection figures(vector<Figure*>({
        &leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane,
        &sphere1, &sphere2, &sphere3, &cylinder1, &cylinder2, &cylinder3
    }));
    */



    /* LIGHTS */
    Light light(Point(0, 0.5, 0), Color(1,1,1)); // Light source with a pinkish color
    //ceilingPlane.setEmission(Color(1,1,1));
    vector<shared_ptr<Light>> lights = vector<shared_ptr<Light>>({
        make_shared<Light>(light)
    });
    //Camera 

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);
    size_t width = settings.IMAGE_WIDTH;
    size_t height = settings.IMAGE_WIDTH;
    Camera camera(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    camera.setHeight(height);
    camera.setWidth(width);
    
    PPM image;
    
    {
        ScopedTimer timer("Render Timer");
        std::cout << "Rendering..." << std::endl;
        image = camera.render(figures, lights);
    }

    std::cout << "Tone Mapping...\n" << std::endl;
    gammaAndClamping(image, 2.2, 1);
    std::cout << "Saving image...\n" << std::endl;

    image.save(settings.OUTPUT_FILE);
    
    cout << "Done." << endl;
    
    if(settings.OPEN_IMAGE_VIEWER_AFTER_RENDER){
        std::cout << "Opening image...\n" << std::endl;
        try{
            std::string cmd = "start " + settings.IMAGE_VIEWER_PATH + " " +  settings.OUTPUT_FILE;
            system(cmd.c_str());
            
        }catch(const std::exception& e){
            cerr << "Error opening Image: " << e.what() << endl;
        }
    }

    return 0;
}   

/**
 * @brief Parsea los argumentos de la linea de comandos y actualiza las configuraciones globales.
 * 
 * Esta funcion utiliza `parse_command_line` para procesar los argumentos proporcionados
 * en la linea de comandos y ajustar las configuraciones globales del programa.
 * En caso de error, imprime un mensaje y muestra la ayuda.
 * 
 * @param argc Numero de argumentos.
 * @param argv Array de argumentos.
 */
void parseArgs(int argc, char* argv[]){
    try {
        parse_command_line(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n\n";
        print_help(argv[0]);
        exit(1);
    }
    std::cout << "================== Configuration ==================\n";
    std::cout << "MAX_BOUNCES   = " << settings.MAX_BOUNCES << "\n"
              << "MAX_PATHS     = " << settings.MAX_PATHS << "\n"
              << "RAYS_PER_PX   = " << settings.MAX_RAYS_PER_PIXEL << "\n"
              << "WIDTH         = " << settings.IMAGE_WIDTH << "\n"
              << "HEIGHT        = " << settings.IMAGE_HEIGHT << "\n"
              << "MAX_PHOTONS   = " << settings.MAX_PHOTONS << "\n"
              << "MAX_NEIGHBORS = " << settings.MAX_NEIGHBORS << "\n"
              << "OUTPUT_FILE   = " << settings.OUTPUT_FILE << "\n"
              << "VIEWER_PATH   = " << settings.IMAGE_VIEWER_PATH << "\n"
              << "OPEN_VIEWER   = " << (settings.OPEN_IMAGE_VIEWER_AFTER_RENDER ? "true" : "false") << "\n"
              << "SCENE         = " << settings.SCENE_NUMBER << "\n";
    std::cout << "===================================================\n" << std::endl;

}