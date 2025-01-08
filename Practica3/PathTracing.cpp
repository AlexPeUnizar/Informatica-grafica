#include "PathTracing.hpp"

RR_Events russianRoulette(double kdWeight, double ksWeight, double ktWeight){
    double rand = randomDouble(0,1);
    float total = kdWeight + ksWeight + ktWeight;
    if (rand < kdWeight / total) return DIFUSSE; // Difuso
    else if (rand < (kdWeight + ksWeight) / total) return SPECULAR; // Especular
    else return REFRACTIVE; // Refracción
}
