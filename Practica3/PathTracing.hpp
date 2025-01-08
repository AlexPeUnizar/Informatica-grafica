#ifndef PATHTRACING_HPP
#define PATHTRACING_HPP

#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <string>

#include "Vector.hpp"
#include "Point.hpp"
#include "Coordinate.hpp"
#include "Matrix.hpp"
#include "Figure.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "Triangle.hpp"
#include "TriangleMesh.hpp"
#include "Plane.hpp"
#include "Camera.hpp"
#include "PPM.hpp"
#include "FigureCollection.hpp"
#include "Light.hpp"
#include "Materials.hpp"
#include "Color.hpp"
#include "ScopedTimer.hpp"
#include "Utils.hpp"

/* SETTINGS */
const size_t MAX_RAYS_PER_PIXEL = 512;

/* RUSSIAN ROULETTE */
enum RR_Events{
    DIFUSSE,
    SPECULAR,
    REFRACTIVE,
    ABSORTION
};

/* FUNCTIONS */

RR_Events russianRoulette(double kdWeight, double ksWeight, double ktWeight);

#endif /* PATHTRACING_HPP */