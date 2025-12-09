#define _USE_MATH_DEFINES
#include "Utils.hpp"
#include <cstdlib>
#include <time.h>
#include <math.h>

Settings settings;

double randomDouble(double min, double max){
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

double randomDouble(){
    return randomDouble(0.0, 1.0);
}

Vector randomDirection(){
    double theta = 2 * M_PI * randomDouble(0, 1); 
    double phi = acos(2 * randomDouble(0, 1) - 1);
    return Vector(
        sin(phi) * cos(theta),
        sin(phi) * sin(theta),
        cos(phi)
    );
}

Vector randomDirection(const Point& point, const Vector& normal){
    Vector random;
    double phi = 2 * M_PI * randomDouble(0, 1);
    double theta = asin(sqrt(randomDouble(0, 1)));

    random = Vector(
        sin(theta) * cos(phi),
        sin(theta) * sin(phi),
        cos(theta)
    );
    Vector randomBaseVector(0,1,0);
    double alpha = angle(normal, randomBaseVector);
    if (std::abs(alpha - M_PI) < 1e-6 || std::abs(alpha) < 1e-6) {
        randomBaseVector = Vector(1, 0, 0);
    }   
    Vector T = normalize(crossProduct(normal, randomBaseVector));
    Vector B = normalize(crossProduct(normal, T));

    Vector randomVector = baseChange(
        point,
        T,
        B,
        normal
    ) * random;

    return randomVector;
}


/**
 * @brief Muestra el mensaje de uso del programa con las opciones disponibles.
 * 
 * @param progname Nombre del programa (generalmente argv[0]).
 * 
 * Este metodo imprime en la salida estandar un mensaje detallado sobre como usar
 * el programa, incluyendo las opciones disponibles y sus descripciones. Las opciones
 * incluyen configuraciones como el numero maximo de rebotes, paths, rayos por pixel,
 * dimensiones de la imagen, nombre del archivo de salida, ruta al visor de imagenes,
 * y la posibilidad de abrir el visor automaticamente despues de renderizar.
 */
static void print_usage(const char* progname) {
    std::cout << "Uso: " << progname << " [opciones]\n\n"
              << "Opciones:\n"
              << "  --help                       Muestra esta ayuda\n"
              << "  --max-bounces N              Numero maximo de rebotes (size_t)\n"
              << "  --max-paths N                Numero maximo de paths (size_t)\n"
              << "  --max-rays-per-pixel N       Rays por pixel (size_t)\n"
              << "  --width N                    Ancho de imagen (size_t)\n"
              << "  --height N                   Alto de imagen (size_t)\n"
              << "  --max-photons N              Numero maximo de fotones (size_t)\n"
              << "  --max-neighbors N            Numero maximo de vecinos para busqueda de fotones (size_t)\n"
              << "  --output FILE                Nombre de fichero de salida\n"
              << "  --viewer-path PATH           Ruta al programa visor de imagen\n"
              << "  --open-viewer                Abrir visor despues de renderizar\n"
              << "  --scene N                    Seleccionar escena [1,2,3,4]\n"
              << "      Las escenas son:\n"
              << "          -1: ...\n"
              << "          -2: ...\n"
              << "          -3: ...\n"
              << "          -4: ...\n";
}

/**
 * @brief Muestra el mensaje de ayuda del programa.
 * 
 * @param progname Nombre del programa (generalmente argv[0]).
 * 
 * Este metodo llama a print_usage para mostrar el mensaje de uso del programa.
 */
void print_help(const char* progname) {
    print_usage(progname);
}

/**
 * @brief Parsea los argumentos de linea de comandos para configurar las opciones del programa.
 * 
 * @param argc Numero de argumentos.
 * @param argv Array de cadenas que representan los argumentos.
 * 
 * Esta funcion procesa los argumentos proporcionados en la linea de comandos
 * y ajusta las configuraciones globales del programa en consecuencia. Soporta
 * varias opciones como el numero maximo de rebotes, paths, rayos por pixel,
 * dimensiones de la imagen, nombre del archivo de salida, ruta al visor de imagenes,
 * y la opcion de abrir el visor automaticamente despues de renderizar.
 * Si se encuentra una opcion desconocida o falta un valor requerido, se lanza
 * una excepcion std::runtime_error.
 */
void parse_command_line(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        auto need_value = [&](const char* opt_name) {
            if (i + 1 >= argc) {
                throw std::runtime_error(
                    std::string("Falta valor para ") + opt_name);
            }
        };

        if (arg == "--help") {
            print_usage(argv[0]);
            std::exit(0);
        }
        else if (arg == "--max-bounces") {
            need_value("--max-bounces");
            settings.MAX_BOUNCES = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--max-paths") {
            need_value("--max-paths");
            settings.MAX_PATHS = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--max-rays-per-pixel") {
            need_value("--max-rays-per-pixel");
            settings.MAX_RAYS_PER_PIXEL = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--width") {
            need_value("--width");
            settings.IMAGE_WIDTH = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--height") {
            need_value("--height");
            settings.IMAGE_HEIGHT = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--max-photons") {
            need_value("--max-photons");
            settings.MAX_PHOTONS = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--max-neighbors") {
            need_value("--max-neighbors");
            settings.MAX_NEIGHBORS = static_cast<std::size_t>(std::stoul(argv[++i]));
        }
        else if (arg == "--output") {
            need_value("--output");
            settings.OUTPUT_FILE = argv[++i];
        }
        else if (arg == "--viewer-path") {
            need_value("--viewer-path");
            settings.IMAGE_VIEWER_PATH = argv[++i];
        }
        else if (arg == "--open-viewer") {
            settings.OPEN_IMAGE_VIEWER_AFTER_RENDER = true;
        }
        else if (arg == "--scene") {
            need_value("--scene");
            int scene_number = std::stoi(argv[++i]);
            if (scene_number < 1 || scene_number > 4) {
                throw std::runtime_error("Numero de escena invalido: " + std::to_string(scene_number));
            }
            settings.SCENE_NUMBER = scene_number;
        }
        else {
            throw std::runtime_error("Opcion desconocida: " + arg);
        }
    }
}
