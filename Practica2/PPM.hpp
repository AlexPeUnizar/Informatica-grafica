#ifndef PPM_HPP
#define PPM_HPP
#include <iostream>

class PPM{
private:    
    std::string fileName;
    std::string version;
    int32_t maxFileValue;
    int32_t height, width;
    int32_t maxColorValue;

private:
    double toMemoryValue(double s);
    double toFileValue(double v);

public:
    PPM(const std::string& fileName);
    PPM();
    ~PPM();

    void load(const std::string& fileName);
};


#endif /*PPM_HPP*/