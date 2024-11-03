#include <math.h>
#include "Materials.hpp"
#include "FigureCollection.hpp"

Materials::Lambertian::Lambertian(const Color& color){
    this->color = color;
}

Materials::Lambertian::Lambertian(double r, double g, double b){
    this->color = Color(r,g,b);
}

Color Materials::Lambertian::emission(const Ray& ray, const Intersection& intersection, const Light& light, const IntersectableFigure& scene) const{
    Color end;
    Vector shadowRayDirection = light.getCenter() - intersection.intersectionPoint;

    Ray shadowRay(
        intersection.intersectionPoint,
        normalize(shadowRayDirection)      
    );

    Intersection shadowIntersection;
    if(scene.isIntersectedBy(shadowRay, 0.00001f, module(shadowRayDirection), shadowIntersection)){
        return end;
    }
    
    Color term1 = (this->color * light.getPower() / pow(module(shadowRayDirection), 2));

    double term2 = this->kd / M_PI;
    double term3 = (
        dotProduct(
            intersection.normal,
            (shadowRayDirection) / module(shadowRayDirection)
        )
    );

    end = term1 * term2 * term3;   

    return end;
}