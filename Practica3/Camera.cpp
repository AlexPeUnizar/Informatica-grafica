#include "Camera.hpp"

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