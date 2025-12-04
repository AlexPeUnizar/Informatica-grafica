/**
 * @file Materials.cpp
 * @brief Implementacion de los materiales para el sistema de renderizado, incluyendo modelos Lambertiano y Metálico.
 * 
 * Este archivo contiene la definicion de los metodos asociados a los materiales utilizados en la simulacion de iluminacion,
 * tales como Lambertian y Metal, permitiendo calcular el color resultante en funcion de la interaccion de los rayos de luz
 * con las superficies de las figuras de la escena.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#define _USE_MATH_DEFINES

#include <math.h>
#include <limits.h>
#include "Materials.hpp"
#include "FigureCollection.hpp"

/**
 * @brief Constructor de la clase Material.
 * 
 * Inicializa un material con un color especifico.
 * 
 * @param color Color del material.
 */
Materials::Lambertian::Lambertian(const Color& color): Material(color){
    this->kd = color;
    this->color = color;
}

/**
 * @brief Constructor de la clase Lambertian con valores RGB.
 * 
 * Inicializa un material Lambertiano con un color definido por sus componentes RGB.
 * 
 * @param r Componente rojo del color.
 * @param g Componente verde del color.
 * @param b Componente azul del color.
 */
Materials::Lambertian::Lambertian(double r, double g, double b): Material(Color::fromRGB(r,g,b)){
    this->color = Color(r,g,b);
    this->kd = color;
}

/**
 * @brief Metodo que calcula el color resultante de un rayo en una interseccion con un material Lambertiano.
 * 
 * Este metodo implementa el algoritmo de path tracing para calcular la iluminacion directa e indirecta
 * en una interseccion, utilizando la ruleta rusa para seleccionar eventos de dispersion y generando rayos aleatorios
 * para simular la luz difusa.
 * 
 * @param ray Rayo incidente que interactua con el material.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @param lights Lista de luces presentes en la escena.
 * @param scene Escena que contiene las figuras y sus materiales.
 * @param depth Profundidad actual del rayo en el trazado de rayos.
 * @return Color Resultado del color calculado en la interseccion.
 */
Color Materials::Lambertian::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth) const{
    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < settings.MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        //random ray
        Vector randomVector = randomDirection(ray, intersection);
        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;

        if(depth < settings.MAX_BOUNCES && scene.isIntersectedBy(randomRay, 0.00001f, INT_MAX, randomRayIntersection)){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, depth+1);            
        }

        final += luzDirecta + (luzIndirecta * M_PI * this->brdf(ray,intersection));

    }
    final /= double(settings.MAX_PATHS);
    return final;

}

/**
 * @brief Metodo que calcula la funcion BRDF (Bidirectional Reflectance Distribution Function) para un material Lambertiano.
 * 
 * Este metodo devuelve el valor de la BRDF para un material Lambertiano, que es constante y se define como
 * el color difuso dividido por pi (M_PI).
 * 
 * @param ray Rayo incidente.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @return Color Resultado de la BRDF para el material Lambertiano.
 */
Color Materials::Lambertian::brdf(const Ray& ray, const Intersection& intersection) const{
    return (this->kd / M_PI);
}

/**
 * @brief Constructor de la clase Metal.
 * 
 * Inicializa un material metálico con un color especifico.
 * 
 * @param color Color del material metálico.
 */
Materials::Metal::Metal(const Color& color): Material(color){
    this->kd = color;
    this->color = color;
}

/**
 * @brief Constructor de la clase Metal con valores RGB.
 * 
 * Inicializa un material metálico con un color definido por sus componentes RGB.
 * 
 * @param r Componente rojo del color.
 * @param g Componente verde del color.
 * @param b Componente azul del color.
 */
Materials::Metal::Metal(double r, double g, double b): Material(Color::fromRGB(r,g,b)){
    this->color = Color(r,g,b);
    this->kd = color;
}

/**
 * @brief Metodo que calcula el color resultante de un rayo en una interseccion con un material metálico.
 * 
 * Este metodo implementa el algoritmo de path tracing para calcular la iluminacion directa e indirecta
 * en una interseccion, utilizando la ruleta rusa para seleccionar eventos de reflexion especular y generando rayos reflejados
 * para simular la luz especular.
 * 
 * @param ray Rayo incidente que interactua con el material.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @param lights Lista de luces presentes en la escena.
 * @param scene Escena que contiene las figuras y sus materiales.
 * @param depth Profundidad actual del rayo en el trazado de rayos.
 * @return Color Resultado del color calculado en la interseccion.
 */
Color Materials::Metal::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth) const{
    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < settings.MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        Vector reflectedVector = reflect(ray.dir, intersection.normal);
        Ray reflectedRay = Ray(intersection.intersectionPoint, reflectedVector);
        Intersection reflectedRayIntersection;

        if(depth < settings.MAX_BOUNCES && scene.isIntersectedBy(reflectedRay, 0.00001f, INT_MAX, reflectedRayIntersection)){
            luzIndirecta = reflectedRayIntersection.material->getColor(reflectedRay, reflectedRayIntersection, lights, scene, depth+1);            
        }

        final += luzDirecta + (luzIndirecta * M_PI  *this->brdf(ray,intersection));

    }
    final /= double(settings.MAX_PATHS);
    return final;
}

/**
 * @brief Metodo que calcula la funcion BRDF (Bidirectional Reflectance Distribution Function) para un material metálico.
 * 
 * Este metodo devuelve el valor de la BRDF para un material metálico, que es constante y se define como
 * el color difuso dividido por pi (M_PI).
 * 
 * @param ray Rayo incidente.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @return Color Resultado de la BRDF para el material metálico.
 */
Color Materials::Metal::brdf(const Ray& ray, const Intersection& intersection) const{
    return (this->kd / M_PI);
}

