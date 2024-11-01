#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "FigureCollection.hpp"
#include "PPM.hpp"
#include "Light.hpp"

class Camera{
private:
    Vector up;
    Vector left;
    Vector front;
    Point o;
    size_t height;
    size_t width;
public:
    Camera(const Vector& up, const Vector& left,const Vector& front, const Point& o);
    ~Camera();
    Vector& getUp();    
    Vector& getLeft();    
    Vector& getFront();    
    Point& getO();    
    size_t& getHeight();    
    size_t& getWidth();
    void setHeight(const size_t height);    
    void setWidth(const size_t width);   
    Ray getRayToPixel(size_t x, size_t y); 
    PPM render(FigureCollection& scene, Light& light);
};

#endif /* CAMERA_HPP */