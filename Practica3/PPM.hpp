#ifndef PPM_HPP
#define PPM_HPP
#include <iostream>
#include <memory>
#include <vector>
#include "Color.hpp"

class PPM{
public:
    struct Pixel{
        double r, g, b;
        Pixel(Color color){
            this->r = color.r*255.0;
            this->g = color.g*255.0;
            this->b = color.b*255.0;
        }
        Pixel(double r, double g, double b){
            this->r = r;
            this->g = g;
            this->b = b;
        }
    };
private:    
    std::string fileName;
    std::string version;
    double realMaxColorValue;
    int32_t height, width;
    int32_t maxColorValue;    
    std::vector<std::vector<std::shared_ptr<Pixel>>> pixels;

private:
    double toMemoryValue(double s);
    double toFileValue(double v);

public:
    PPM(const std::string& fileName);
    PPM() = default;
    PPM(int32_t height, int32_t width);
    ~PPM();

    void load(const std::string& fileName);
    void save(const std::string& fileName = "out.ppm");
    std::vector<std::shared_ptr<Pixel>>& operator[](std::size_t idx){ return pixels[idx]; }
    const std::vector<std::shared_ptr<Pixel>>& operator[](std::size_t idx) const{ return pixels[idx]; }
    friend std::ostream& operator<<(std::ostream& os, const PPM& image);

    friend void clamping(PPM& image, double clampValue);
    friend void equalization(PPM& image);
    friend void equalizationAndClamping(PPM& image, const double clampValue);
    friend void gamma(PPM& image, double gammaValue);
    friend void gammaAndClamping(PPM& image, double gammaValue, double clampValue);  
};


#endif /*PPM_HPP*/