#define _USE_MATH_DEFINES
#include <cmath>
#include "Material.hpp"
#include "Utils.hpp"

Material::Material(const Color& color){
    this->color = color;
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

Vector Material::randomDirection(const Ray& ray, const Intersection& intersection) const{
    Vector random;
    double phi = 2 * M_PI * randomDouble(0, 1);
    double theta = asin(sqrt(randomDouble(0, 1)));

    random = Vector(
        sin(theta) * cos(phi),
        sin(theta) * sin(phi),
        cos(theta)
    );
    Vector randomBaseVector(0,1,0);
    double alpha = angle(intersection.normal, randomBaseVector);
    if (std::abs(alpha - M_PI) < 1e-6 || std::abs(alpha) < 1e-6) {
        randomBaseVector = Vector(1, 0, 0);
    }   
    Vector T = normalize(crossProduct(intersection.normal, randomBaseVector));
    Vector B = normalize(crossProduct(intersection.normal, T));

    Vector randomVector = baseChange(
        intersection.intersectionPoint,
        T,
        B,
        intersection.normal
    ) * random;

    return randomVector;
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

Color Material::computeDifusse(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth)const{
    Color final(0,0,0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        //random ray
        Vector randomVector = randomDirection(ray, intersection);
        Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
        Intersection randomRayIntersection;

        if(depth < MAX_BOUNCES && scene.isIntersectedBy(randomRay, 0.00001f, INT_MAX, randomRayIntersection)){
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, depth+1);            
        }

        final += luzDirecta + (luzIndirecta * M_PI * this->brdf(ray,intersection));

    }
    final /= double(MAX_PATHS);
    return final;
}

Color Material::computeSpecular(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth)const{
    Color final(0, 0, 0);
    Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for (int path = 0; path < MAX_PATHS; path++) {
        Color luzIndirecta(0, 0, 0);

        // Calcular el vector reflejado
        Vector reflected = reflect(ray.dir, intersection.normal);
        Vector viewDir = normalize(ray.origin - intersection.intersectionPoint);  // Dirección hacia el observador

        // Calculamos la reflexión especular usando el modelo Phong
        double cosTheta = std::max(0.0, dotProduct(reflected, viewDir));  // Ángulo entre el rayo reflejado y el vector de visión
        double specular = pow(cosTheta, 10);  // Exponente especular (puede ajustarse)

        Color specularBRDF = ks * specular;  // Color especular ponderado por ks

        // Calcular iluminación indirecta
        Vector reflectedVector = reflect(ray.dir, intersection.normal);
        Ray reflectedRay(intersection.intersectionPoint, reflectedVector);
        Intersection reflectedRayIntersection;

        if (depth < MAX_BOUNCES && scene.isIntersectedBy(reflectedRay, 0.00001f, INT_MAX, reflectedRayIntersection)) {
            luzIndirecta = reflectedRayIntersection.material->getColor(reflectedRay, reflectedRayIntersection, lights, scene, depth + 1);
        }

        final += luzDirecta + (luzIndirecta * specularBRDF);
    }
    final /= double(MAX_PATHS);
    return final;
}

Color Material::computeRefractive(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth)const{
    Color final(0, 0, 0);
    Color luzDirecta = nextEvent(lights, intersection, scene);
    
    for (int path = 0; path < MAX_PATHS; path++) {
        Color luzIndirecta(0, 0, 0);

        // Calcular la dirección del rayo refractado usando la ley de Snell
        Vector refractedVector = refract(ray.dir, intersection.normal, ior);
        Ray refractedRay(intersection.intersectionPoint, refractedVector);
        Intersection refractedRayIntersection;

        if (depth < MAX_BOUNCES && scene.isIntersectedBy(refractedRay, 0.00001f, INT_MAX, refractedRayIntersection)) {
            luzIndirecta = refractedRayIntersection.material->getColor(refractedRay, refractedRayIntersection, lights, scene, depth + 1);
        }

        // Fresnel-Schlick para determinar la cantidad de reflexión en la interfaz
        double cosTheta = std::max(0.0, dotProduct(intersection.normal, refractedVector));
        double r0 = (1 - ior) / (1 + ior);
        r0 = r0 * r0;
        double F = r0 + (1 - r0) * pow(1 - cosTheta, 5); // Aproximación de Fresnel

        // Aplicamos la reflexión (F) y la refracción (1 - F)
        final += luzDirecta + luzIndirecta * ((1 - F) * M_PI * this->brdf(ray, intersection));
    }
    final /= double(MAX_PATHS);
    return final;   
}
double fresnelSchlick(double cosTheta, double ior){
    double r0 = (1 - ior) / (1 + ior);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow(1 - cosTheta, 5);
}

Color Material::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth) const{
    if (depth >= MAX_BOUNCES) return Color(0, 0, 0);

    // Determinar la probabilidad de continuar el recorrido con la ruleta rusa
    double p_rr = computeRussianRoulette();
    if (randomDouble() > p_rr) return Color(0, 0, 0);  // Si no continuamos, no hay color

    // Inicializar color final
    Color finalColor(0, 0, 0);

    // Calcular la iluminación directa
    Color directLighting = nextEvent(lights, intersection, scene);

    // Calcular la dirección muestreada aleatoriamente (dirección de luz reflejada o transmitida)
    Vector sampledDirection = randomDirection(ray, intersection);
    Ray newRay(intersection.intersectionPoint, sampledDirection);

    // Intersección de la muestra con la escena
    Intersection newIntersection;
    if (scene.isIntersectedBy(newRay, 0.001f, INT_MAX, newIntersection)) {
        // Calcular iluminación indirecta (difusa, especular o refractiva)
        Color indirectLighting;
        
        if (maxComponent(this->kd) != 0) {
            // Llamamos a `computeDifusse` si el material tiene componente difusa
            indirectLighting = computeDifusse(ray, intersection, lights, scene, depth + 1);
        }
        else if (maxComponent(this->ks) != 0) {
            // Llamamos a `computeSpecular` si el material tiene componente especular
            indirectLighting = computeSpecular(ray, intersection, lights, scene, depth + 1);
        }
        else if (maxComponent(this->kt) != 0) {
            // Llamamos a `computeRefractive` si el material tiene componente refractiva
            indirectLighting = computeRefractive(ray, intersection, lights, scene, depth + 1);
        }

        // Agregar la iluminación directa y la indirecta al color final
        finalColor = (directLighting + indirectLighting * brdf(ray, intersection)) / p_rr;
    }

    return finalColor;  
}

Color Material::brdf(const Ray& ray, const Intersection& intersection) const{
    double randComponent = randomDouble();
    if (randComponent < maxComponent(kd)) {
        // Difuso (Lambertiano)
        return kd / M_PI;
    } else if (randComponent < maxComponent(kd) + maxComponent(ks)) {
        // Especular (Phong/GGX)
        Vector reflected = reflect(ray.dir, intersection.normal);
        return ks * reflected;
    } else if (randComponent < maxComponent(kd) + maxComponent(ks) + maxComponent(kt)) {
        // Refracción
        Vector refracted = refract(ray.dir, intersection.normal, ior);
        return kt * refracted;
    }
    return Color(0, 0, 0);  // No interacción
}

double Material::computeRussianRoulette() const {
    double p_continue = std::max(maxComponent(kd) + maxComponent(ks) + maxComponent(kt), 0.1);
    return std::min(p_continue, 1.0);
}
