#include "ToneMapping.hpp"
#include <algorithm>
#include <cmath>

void clamping(PPM& image){
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = std::min(1.0, pixel.get()->r);
            pixel.get()->g = std::min(1.0, pixel.get()->g);
            pixel.get()->b = std::min(1.0, pixel.get()->b);
        }
    }
    image.maxColorValue = 255;
}

void equalization(PPM& image){
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = (((pixel.get()->r) * 1.0) / (image.realMaxColorValue));
            pixel.get()->g = (((pixel.get()->g) * 1.0) / (image.realMaxColorValue));
            pixel.get()->b = (((pixel.get()->b) * 1.0) / (image.realMaxColorValue));
        }
    }
    image.maxColorValue = 255;
}

void equalizationAndClamping(PPM& image, double clampValue){
    //V = image.toMemoryValue(V);
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = (((pixel.get()->r) * clampValue) / (image.realMaxColorValue));
            pixel.get()->g = (((pixel.get()->g) * clampValue) / (image.realMaxColorValue));
            pixel.get()->b = (((pixel.get()->b) * clampValue) / (image.realMaxColorValue));
        }
    }
    clamping(image);
}
void gamma(PPM& image, double gammaValue){
    equalization(image);

    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            
            pixel.get()->r = std::pow(pixel.get()->r, gammaValue);
            pixel.get()->g = std::pow(pixel.get()->g, gammaValue);
            pixel.get()->b = std::pow(pixel.get()->b, gammaValue);
        }
    }
    
    image.maxColorValue = 255;
}

void gammaAndClamping(PPM& image);