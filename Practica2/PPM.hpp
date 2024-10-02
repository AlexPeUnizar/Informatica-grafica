#ifndef PPM_HPP
#define PPM_HPP
#include <iostream>
#include <memory>
#include <vector>

class PPM{
private:    
    std::string fileName;
    std::string version;
    double maxFileValue;
    int32_t height, width;
    int32_t maxColorValue;
    struct Pixel{
        double r, g, b;
    };
    
    std::vector<std::vector<std::shared_ptr<Pixel>>> pixels;

private:
    double toMemoryValue(double s);
    double toFileValue(double v);

public:
    PPM(const std::string& fileName);
    PPM();
    ~PPM();

    void load(const std::string& fileName);
    void save(const std::string& fileName = "out.ppm");

    friend std::ostream& operator<<(std::ostream& os, const PPM& image);
    
};


#endif /*PPM_HPP*/