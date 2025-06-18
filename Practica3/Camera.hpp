
/**
 * @file Camera.hpp
 * @brief Definición de la clase Camera para la representación y renderizado de escenas 3D.
 *
 * Este archivo contiene la declaración de la clase Camera, que representa una cámara en un espacio 3D.
 * La clase permite definir la orientación, posición y resolución de la cámara, así como generar rayos
 * a través de los píxeles de la imagen y renderizar una escena utilizando técnicas de ray tracing.
 *
 * @autor: Alex
 * @date 18-6-2025
 */
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "FigureCollection.hpp"
#include "PPM.hpp"
#include "Light.hpp"

/**
 * @brief Clase Camera para la representación de una cámara en un espacio 3D.
 *
 * La clase Camera permite definir la orientación (vectores up, left, front), la posición (punto o),
 * y la resolución (height, width) de la cámara. Proporciona métodos para obtener rayos a través de
 * los píxeles de la imagen y para renderizar una escena 3D utilizando ray tracing.
 */
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
    PPM render(FigureCollection& scene, std::vector<std::shared_ptr<Light>>& light);
};

#endif /* CAMERA_HPP */