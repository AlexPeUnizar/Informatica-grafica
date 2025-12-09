#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <cstdint>
#include "Point.hpp"
#include "Vector.hpp"

/* SETTINGS */
struct Settings{
    size_t      MAX_BOUNCES                     = 6;
    size_t      MAX_PATHS                       = 1;

    size_t      MAX_RAYS_PER_PIXEL              = 64;

    size_t      MAX_PHOTONS                     = 100000;
    size_t      MAX_NEIGHBORS                   = 100; // Nearest neighbors for photon search

    size_t      IMAGE_WIDTH                     = 1024;
    size_t      IMAGE_HEIGHT                    = 1024;
    std::string OUTPUT_FILE                     = "out.ppm";
    
    std::string IMAGE_VIEWER_PATH               = "\"C:/Program Files/GIMP 3/bin/gimp-3.0.exe\"";
    bool        OPEN_IMAGE_VIEWER_AFTER_RENDER  = false;
    uint16_t    SCENE_NUMBER                    = 1;
};

extern Settings settings;

/* FUNCTIONS */
double randomDouble(double min, double max);
double randomDouble();
Vector randomDirection();
Vector randomDirection(const Point& point, const Vector& normal);

void parse_command_line(int argc, char* argv[]);
void print_help(const char* progname);
#endif /* UTILS_HPP */