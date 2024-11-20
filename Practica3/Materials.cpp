#include <math.h>
#include <limits.h>
#include "Materials.hpp"
#include "FigureCollection.hpp"

Materials::Lambertian::Lambertian(const Color& color){
    this->color = color;
}

Materials::Lambertian::Lambertian(double r, double g, double b){
    this->color = Color(r,g,b);
}

Color Materials::Lambertian::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth) const{
    /*
    Color finalColor;

    Vector randomBounce = randomDirection(ray, intersection);
    Ray bounceRay(intersection.intersectionPoint, randomBounce);
    Intersection bounceIntersection;
    if(scene.isIntersectedBy(bounceRay, 0.00001f, INT_MAX, bounceIntersection)){
        Color bounceEmission = bounceIntersection.material->getColor(bounceRay, bounceIntersection, lights, scene, depth + 1);
    }

    for(const auto& light : lights){
        Vector shadowRayDirection = light->getCenter() - intersection.intersectionPoint;
        Ray shadowRay(
            intersection.intersectionPoint,
            normalize(shadowRayDirection)      
        );

        Intersection shadowIntersection;
        if(scene.isIntersectedBy(shadowRay, 0.00001f, module(shadowRayDirection), shadowIntersection)){
            finalColor += Color(0, 0, 0);
        }else {
            Color term1 = (light->getPower() / pow(module(shadowRayDirection), 2));

            Color term2 = this->brdf(ray, intersection);
            double term3 = abs(
                dotProduct(
                    intersection.normal,
                    (shadowRayDirection) / module(shadowRayDirection)
                )
            );

            finalColor += term1 * term2 * term3;   
        }
    }
    finalColor /= lights.size();

    return finalColor;
    */
    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    for(int path = 0; path < MAX_BOUNCES; path++){
        Vector randomVector = randomDirection(ray, intersection);

        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;
        Color luzIndirecta(0,0,0);

        if(scene.isIntersectedBy(randomRay, 0.00001f, 2.0f, randomRayIntersection) && depth < MAX_BOUNCES){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, depth+1);
        }


        final += M_PI * ( this->brdf(ray, intersection)) + luzIndirecta /* * abs(dotProduct(intersection.normal, randomVector))*/;
    }
    return final / MAX_BOUNCES;

}

Color Materials::Lambertian::brdf(const Ray& ray, const Intersection& intersection) const{
    return this->color * (this->kd / M_PI);
}
