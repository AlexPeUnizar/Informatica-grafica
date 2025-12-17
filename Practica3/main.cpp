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
    SceneData scene = buildScene1();
    switch(settings.SCENE_NUMBER) {
        case 1: scene = buildScene1(); break;
        case 2: scene = buildScene2(); break;
        case 3: scene = buildScene3(); break;
        case 4: scene = buildScene4(); break;
        default: scene = buildScene1(); break;
    }

    PPM image;
    {
        ScopedTimer timer("Render Timer");
        std::cout << "Rendering..." << std::endl;
        image = scene.camera.render(scene.figures, scene.lights);
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