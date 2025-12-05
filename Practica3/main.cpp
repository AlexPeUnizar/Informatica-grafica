/**
 * @file main.cpp
 * @brief Punto de entrada principal para la aplicacion de renderizado Path Tracing.
 *
 * Este programa configura una escena 3D sencilla con planos y esferas, define materiales,
 * una fuente de luz y renderiza la escena usando un algoritmo de path tracing.
 * La imagen renderizada se guarda en formato PPM y se abre automaticamente con GIMP.
 *
 * Dependencias:
 * - PathTracing.hpp y clases relacionadas de escena, materiales y geometria.
 *
 * @author Alex
 * @date 18-6-2025
 */
#include "PathTracing.hpp"
#include <iostream>

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
            Color(0.0, 0.0, 0.0),  // kt: Sin refraccion
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
            1.5                    // ior (indice de refraccion)
        )
    );

    // Integracion en el FigureCollection
    FigureCollection figures(vector<Figure*>(
        {
            &leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, 
            &leftSphere, &rightSphere
        }
    ));

    

    /* LIGHTS */
    //ceilingPlane.setEmission(Color(1,1,1)); // Luz ambiental suave desde el techo
    Light light(Point(0, 0.7, 0), Color(1,1,1));
    //Light light2(Point(0, 05, 0), Color(1,0,1));
    vector<shared_ptr<Light>> lights = vector<shared_ptr<Light>>({
        make_shared<Light>(light)
    });
    //Camera 

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);
    size_t width = settings.IMAGE_WIDTH;
    size_t height = settings.IMAGE_HEIGHT;
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
    
    std::cout << "Done.\n" << endl;

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
    std::cout << "MAX_BOUNCES = " << settings.MAX_BOUNCES << "\n"
              << "MAX_PATHS   = " << settings.MAX_PATHS << "\n"
              << "RAYS_PER_PX = " << settings.MAX_RAYS_PER_PIXEL << "\n"
              << "WIDTH       = " << settings.IMAGE_WIDTH << "\n"
              << "HEIGHT      = " << settings.IMAGE_HEIGHT << "\n"
              << "OUTPUT_FILE = " << settings.OUTPUT_FILE << "\n"
              << "VIEWER_PATH = " << settings.IMAGE_VIEWER_PATH << "\n"
              << "OPEN_VIEWER = " << (settings.OPEN_IMAGE_VIEWER_AFTER_RENDER ? "true" : "false") << "\n"
              << "SCENE       = " << settings.SCENE_NUMBER << "\n";
    std::cout << "===================================================\n" << std::endl;

}