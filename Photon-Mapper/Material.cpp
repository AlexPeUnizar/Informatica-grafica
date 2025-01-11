#define _USE_MATH_DEFINES
#include <math.h>
#include "Material.hpp"
#include "Utils.hpp"

RR_Event russianRoulette(Color kdWeight, Color ksWeight, Color ktWeight){
    double pDiffuse = maxComponent(kdWeight);
    double pSpecular = maxComponent(ksWeight);
    double pRefractive = maxComponent(ktWeight);

    double rand = randomDouble(0, 1);
    double total = pDiffuse + pSpecular + pRefractive;
    
    if (rand < pDiffuse / total) return {DIFUSSE, pDiffuse/total}; 
    else if (rand < (pDiffuse + pSpecular) / total) return {SPECULAR, pSpecular/total}; 
    else if (rand < (pDiffuse + pSpecular + pRefractive) / total) return {REFRACTIVE, pRefractive/total}; 
    else return {ABSORTION, rand};
}

Vector Material::getSacterredVector(const Ray &ray, const Intersection &intersection, const RR_Event event) const{
    switch (event.eventType){
        case DIFUSSE:
            return randomDirection(intersection.intersectionPoint, intersection.normal);
            break;  
        case SPECULAR:
            return reflect(ray.dir, intersection.normal);
            break;
        case REFRACTIVE:
            return refract(ray.dir, intersection.normal, this->ior);
            break;
        default:
            return Vector(0,0,0);
            break;
    }
}

Material::Material(const Color& color){
    this->kd = color;    
    this->ks = Color(0, 0, 0);
    this->kt = Color(0, 0, 0);
    this->ior = 0;
}

Material::Material(const Color& kd, const Color& ks, const Color& kt, double ior){
    this->kd = kd;    
    this->ks = ks;
    this->kt = kt;
    this->ior = ior;
}

void Material::setColor(const Color& color){
    this->color = color;
}

Color Material::nextEvent(const std::vector<std::shared_ptr<Light>>& lights, const Intersection& intersection, const IntersectableFigure& scene) const{
    Color finalColor;

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
            Color term2 = this->brdf(Ray(), intersection);
            double term3 = abs(
                dotProduct(
                    intersection.normal,
                    (shadowRayDirection) / module(shadowRayDirection)
                )
            );

            finalColor += term1 * term2 * term3;   
        }
    }
    finalColor /= double(lights.size());

    return finalColor;
}

Color Material::calculateIllumination(const std::vector<const Photon*>& nearestPhotons, const Intersection& intersection) const {
    Color result(0, 0, 0);
    int numPhotons = nearestPhotons.size();

    for (const Photon* photon : nearestPhotons) {

            // Asumimos que brdf necesita un rayo; aquí usamos un rayo con dirección dummy
            // Asegúrate de que la dirección sea consistente con cómo se esperan los argumentos de brdf
            Vector incoming = normalize(intersection.intersectionPoint - photon->getPosition());
            Ray incomingRay(photon->getPosition(), incoming);
            Color photonContribution = photon->getFlux() * intersection.material->brdf(incomingRay, intersection);

            result += photonContribution;
        
    }

    if (numPhotons > 0) {
        result /= numPhotons;  // Promedia la contribución de los fotones, considera quitar si se maneja la normalización correctamente
    }

    return result;
}


Color Material::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth) const{
    
    //auto nearestPhotons = search_nearest(photonMap, intersection.intersectionPoint, 50, 0.1);
    if (depth >= MAX_BOUNCES) return Color(0, 0, 0);

    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        RR_Event event = russianRoulette(kd, ks, kt);
        
        if(event.eventType == ABSORTION){
            continue;
        }

        Vector randomVector = getSacterredVector(ray, intersection, event);
        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;

        if(depth < MAX_BOUNCES && scene.isIntersectedBy(randomRay, 0.00001f, INT_MAX, randomRayIntersection)){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, photonMap, depth+1);            
        }
        
        final += luzDirecta + (luzIndirecta * bsdf(randomRay, intersection, event) ) ;
        
    }
    final /= double(MAX_PATHS);
    return final;
}

Color Material::brdf(const Ray& ray, const Intersection& intersection) const{
    return this->kd / M_PI;
}

Color Material::bsdf(const Ray& ray, const Intersection& intersection, const RR_Event event) const{
    switch (event.eventType){
        case DIFUSSE:
            return this->kd  / (event.probability);
            break;
        case SPECULAR:
            return this->ks / (event.probability );
            break;
        case REFRACTIVE:
            return this->kt / (event.probability );
            break;
        default:
            return Color(0,0,0);
            break;
    }
}

/*
Color Material::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth) const{
    if (depth >= MAX_BOUNCES) return Color(0, 0, 0);

    // Calcula las probabilidades para difuso, especular y refractivo
    double pDiffuse = maxComponent(this->kd);
    double pSpecular = maxComponent(this->ks);
    double pRefractive = maxComponent(this->kt);

    double sum = pDiffuse + pSpecular + pRefractive;
    if (sum > 0) {
        pDiffuse /= sum;
        pSpecular /= sum;
        pRefractive /= sum;
    } else {
        pDiffuse = 0.0;
        pSpecular = 0.0;
        pRefractive = 0.0;
    }

    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        //random ray
        double randomValue = randomDouble();

        Vector randomVector;
        // Determina el evento según el valor aleatorio
        if (randomValue < pDiffuse) {
            // Evento difuso
            randomVector = randomDirection(ray, intersection);
        } else if (randomValue < pDiffuse + pSpecular) {
            // Evento especular
            randomVector = reflect(ray.dir, intersection.normal);
            
        } else if (randomValue < pDiffuse + pSpecular + pRefractive) {
            // Evento refractivo
            randomVector = refract(ray.dir, intersection.normal, this->ior);
        } else{
            return Color(0,0,0);
        }

        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;

        if(depth < MAX_BOUNCES && scene.isIntersectedBy(randomRay, 0.00001f, INT_MAX, randomRayIntersection)){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, depth+1);            
        }
        if (randomValue < pDiffuse) {
            // Evento difuso
            final += luzDirecta + (luzIndirecta * kd);

        } else if (randomValue < pDiffuse + pSpecular) {
            // Evento especular
            final += luzDirecta + (luzIndirecta * M_PI * ks);

        } else {
            // Evento refractivo
            final += luzDirecta + (luzIndirecta * M_PI * kt);
        }
        

    }
    final /= double(MAX_PATHS);
    return final;
}

 */