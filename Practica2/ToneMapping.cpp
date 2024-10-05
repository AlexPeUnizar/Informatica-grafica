#include "ToneMapping.hpp"

void clamping(PPM& image){
    for (size_t i = 0; i < image.height; i++){
        for (size_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            if(pixel.get()->r > 1.0){
                pixel.get()->r = 1.0;
            }
            if(pixel.get()->g > 1.0){
                pixel.get()->g = 1.0;
            }
            if(pixel.get()->b > 1.0){
                pixel.get()->b = 1.0;
            }
        }
    }
    image.maxColorValue = 255;
}

void equalization(PPM& image){
    for (size_t i = 0; i < image.height; i++){
        for (size_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = (((pixel.get()->r)*65535)/(image.maxColorValue));
            pixel.get()->g = (((pixel.get()->g)*65535)/(image.maxColorValue));
            pixel.get()->b = (((pixel.get()->b)*65535)/(image.maxColorValue));
        }
    }
    image.maxColorValue = 65535;
}

void equalizationAndClamping(PPM& image);
void gamma(PPM& image);
void gammaAndClamping(PPM& image);