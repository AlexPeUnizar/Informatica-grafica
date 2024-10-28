#include "Camera.hpp"
#include "Utils.hpp"

Camera::Camera(const Vector& up,const Vector& left,const Vector& front,const Point& o){
    this->up = up;
    this->left = left;
    this->front = front;
    this->o = o;
}

Camera::~Camera(){
    this->up.~Vector();    
    this->left.~Vector();    
    this->front.~Vector();    
    this->o.~Point();    
}

Vector& Camera::getUp(){
    return this->up;
}   

Vector& Camera::getLeft(){
    return this->left;
}   

Vector& Camera::getFront(){
    return this->front;
}   

Point& Camera::getO(){
    return this->o;
}   

size_t& Camera::getHeight(){
    return this->height;
}   

size_t& Camera::getWidth(){
    return this->width;
}

void Camera::setHeight(const size_t height){
    this->height = height;     
}    

void Camera::setWidth(const size_t width){
    this->width = width; 
}

Ray Camera::getRayToPixel(size_t x, size_t y){
    Vector upperLeft = this->front + this->left + this->up;

    Vector vectorToUpperCorner = upperLeft + 
                            this->left * -2 * (double(x)/double(this->width)) + 
                            this->up * -2 * (double(y)/double(this->height));
    Vector vectorToLowerCorner = upperLeft + 
                            this->left * -2 * (double(x+1)/double(this->width)) + 
                            this->up * -2 * (double(y+1)/double(this->height));

    Point upCorner = Ray(this->o, normalize(vectorToUpperCorner)).at(module(vectorToUpperCorner));
    Point downCorner = Ray(this->o, normalize(vectorToLowerCorner)).at(module(vectorToLowerCorner));

    Point p = Point(randomDouble(upCorner.x, downCorner.x), randomDouble(downCorner.y, upCorner.y), upCorner.z);
    Ray ray(this->o, p - this->o);
    
    return ray;
}
