#define _USE_MATH_DEFINES

#include <math.h>
#include <limits.h>
#include "Materials.hpp"
#include "FigureCollection.hpp"
#include "Utils.hpp"

Materials::Lambertian::Lambertian(const Color& color): Material(color){
    this->kd = color;
    this->color = color;
}

Materials::Lambertian::Lambertian(double r, double g, double b): Material(Color::fromRGB(r,g,b)){
    this->color = Color(r,g,b);
    this->kd = color;
}

Color Materials::Lambertian::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth) const{
    /*Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        //random ray
        Vector randomVector = randomDirection(intersection.intersectionPoint, intersection.normal);
        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;

        if(depth < MAX_BOUNCES && scene.isIntersectedBy(randomRay, 0.00001f, INT_MAX, randomRayIntersection)){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, photonMap, depth+1);            
        }

        final += luzDirecta + (luzIndirecta * M_PI * this->brdf(ray,intersection));

    }
    final /= double(MAX_PATHS);
    return final;*/
    
    if (depth >= MAX_BOUNCES) return Color(0, 0, 0); // Caso base de recursión

    // Calcula la iluminación directa utilizando el método nextEvent
    Color directLighting = nextEvent(lights, intersection, scene);

    // Estimación de la iluminación indirecta utilizando el mapa de fotones
    auto nearestPhotons = search_nearest(photonMap, intersection.intersectionPoint, 50, 0.2); // 50 fotones y radio de 0.1
    Color indirectLighting = calculateIllumination(nearestPhotons, intersection);
    
    // Combine direct and indirect lighting
    return directLighting + indirectLighting;

}

Color Materials::Lambertian::brdf(const Ray& ray, const Intersection& intersection) const{
    return (this->kd / M_PI);
}

Materials::Metal::Metal(const Color& color): Material(color){
    this->kd = color;
    this->color = color;
}

Materials::Metal::Metal(double r, double g, double b): Material(Color::fromRGB(r,g,b)){
    this->color = Color(r,g,b);
    this->kd = color;
}

Color Materials::Metal::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth) const{
    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        Vector reflectedVector = reflect(ray.dir, intersection.normal);
        Ray reflectedRay = Ray(intersection.intersectionPoint, reflectedVector);
        Intersection reflectedRayIntersection;

        if(depth < MAX_BOUNCES && scene.isIntersectedBy(reflectedRay, 0.00001f, INT_MAX, reflectedRayIntersection)){
            luzIndirecta = reflectedRayIntersection.material->getColor(reflectedRay, reflectedRayIntersection, lights, scene, photonMap, depth+1);            
        }

        final += luzDirecta + (luzIndirecta * M_PI  *this->brdf(ray,intersection));

    }
    final /= double(MAX_PATHS);
    return final;

}

Color Materials::Metal::brdf(const Ray& ray, const Intersection& intersection) const{
    return (this->kd / M_PI);
}

