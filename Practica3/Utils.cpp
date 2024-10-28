#include "Utils.hpp"
#include <cstdlib>
#include <time.h>

double randomDouble(double min, double max){
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

