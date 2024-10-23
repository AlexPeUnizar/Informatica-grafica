#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
#include "Point.hpp"


class Camera{
private:
    Vector up;
    Vector left;
    Vector front;
    Point o;
    size_t height;
    size_t width;
public:
    Camera(Vector& up, Vector& left, Vector& front, Point& o);
    ~Camera();
    Vector& getUp();    
    Vector& getLeft();    
    Vector& getFront();    
    Point& getO();    
    size_t& getHeight();    
    size_t& getWidth();    
};

#endif /* CAMERA_HPP */