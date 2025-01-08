#include "Utils.hpp"
#include <cstdlib>
#include <time.h>

double randomDouble(double min, double max){
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (max - min)));
}

double randomDouble(){
    return randomDouble(0.0, 1.0);
}

