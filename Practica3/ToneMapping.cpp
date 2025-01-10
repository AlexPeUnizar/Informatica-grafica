#include "ToneMapping.hpp"
#include <algorithm>
#include <math.h>

void clamping(PPM& image, double clampValue){
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = std::min(clampValue, pixel.get()->r);
            pixel.get()->g = std::min(clampValue, pixel.get()->g);
            pixel.get()->b = std::min(clampValue, pixel.get()->b);
        }
    }
    image.maxColorValue = 255;
    image.realMaxColorValue = clampValue;
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
    clamping(image, clampValue);
    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            pixel.get()->r = (((pixel.get()->r) * clampValue) / (image.realMaxColorValue));
            pixel.get()->g = (((pixel.get()->g) * clampValue) / (image.realMaxColorValue));
            pixel.get()->b = (((pixel.get()->b) * clampValue) / (image.realMaxColorValue));
        }
    }
}
void gamma(PPM& image, double gammaValue){
    equalization(image);

    for (int32_t i = 0; i < image.height; i++){
        for (int32_t j = 0; j < image.width; j++){
            std::shared_ptr<PPM::Pixel> pixel = image[i][j];
            
            pixel.get()->r = std::pow(pixel.get()->r, 1 / gammaValue);
            pixel.get()->g = std::pow(pixel.get()->g, 1 / gammaValue);
            pixel.get()->b = std::pow(pixel.get()->b, 1 / gammaValue);
        }
    }
    
    image.maxColorValue = 255;
}

void gammaAndClamping(PPM& image, double gammaValue, double clampValue){
    clamping(image, clampValue);
    gamma(image, gammaValue);
}