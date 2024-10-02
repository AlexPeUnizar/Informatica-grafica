#include "PPM.hpp"
#include <iostream>
#include <fstream>
#include <string>

double PPM::toMemoryValue(double s){
        return s * (maxFileValue / maxColorValue);
}

double PPM::toFileValue(double v){
        return v * (maxColorValue / maxFileValue);
}

PPM::PPM(const std::string& nombreArchivo){
    this->load(nombreArchivo);
}

PPM::PPM(){

}

PPM::~PPM(){

}

void PPM::load(const std::string& nombreArchivo){
    
}