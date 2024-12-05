#define _USE_MATH_DEFINES

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
    //std::cout << luzDirecta << std::endl;;
    //std::cin.get();
    for(int path = 0; path < MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        //random ray
        Vector randomVector = randomDirection(ray, intersection);
        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;

        if(depth < MAX_BOUNCES && scene.isIntersectedBy(randomRay, 0.00001f, 9999999.0, randomRayIntersection)){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, depth+1);
            //std::cout << randomRayIntersection.figureName <<std::endl;
            
        }else{
           // std::cout << "It does not intersect" << std::endl;
            if(depth<MAX_BOUNCES){
                //std::cout<<"No hit.  "<< randomRay<< std::endl; 
            }
        }

        final += luzDirecta + (luzIndirecta * M_PI * this->brdf(ray,intersection)) /* * abs(dotProduct(intersection.normal, randomVector))*/;

    }
    //final /= double(MAX_BOUNCES);
    // final *= 255.0;
    //std::cout<<"Depth: "<< depth<< " "<< final <<std::endl;

    return final;

}

Color Materials::Lambertian::brdf(const Ray& ray, const Intersection& intersection) const{
    return this->color * (this->kd / M_PI);
}
