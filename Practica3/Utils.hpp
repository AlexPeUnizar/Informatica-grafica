/**
 * @file Utils.hpp
 * @brief Declaraciones de utilidades para generacion de numeros aleatorios.
 * 
 * Este archivo contiene las declaraciones de funciones auxiliares para la generacion de numeros aleatorios
 * en un rango determinado o en el rango por defecto.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <cstdint>

/* SETTINGS */
struct Settings{
    size_t      MAX_BOUNCES                     = 6;
    size_t      MAX_PATHS                       = 1;

    size_t      MAX_RAYS_PER_PIXEL              = 64;

    size_t      IMAGE_WIDTH                     = 1024;
    size_t      IMAGE_HEIGHT                    = 1024;
    std::string OUTPUT_FILE                     = "out.ppm";
    
    std::string IMAGE_VIEWER_PATH               = "\"C:/Program Files/GIMP 2/bin/gimp-2.10.exe\"";
    bool        OPEN_IMAGE_VIEWER_AFTER_RENDER  = false;
    uint8_t     SCENE_NUMBER                    = 1;
};

extern Settings settings;

/* FUNCTIONS */
double randomDouble(double min, double max);
double randomDouble();

void parse_command_line(int argc, char* argv[]);
void print_help(const char* progname);

#endif /* UTILS_HPP */