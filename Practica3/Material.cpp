/**
 * @file Material.cpp
 * @brief Implementación de la clase Material y funciones relacionadas para el cálculo de la dispersión de la luz en un motor de renderizado basado en trayectorias.
 * 
 * Este archivo contiene la lógica para la simulación de materiales, incluyendo la selección de eventos mediante ruleta rusa,
 * la generación de vectores dispersados, el cálculo de la iluminación directa e indirecta, y la evaluación de las funciones BRDF y BSDF.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include "Material.hpp"

/** 
 * @brief Función que implementa la ruleta rusa para seleccionar un evento de dispersión basado en las propiedades del material.
 * 
 * Esta función calcula la probabilidad de cada tipo de evento (difusa, especular, refractiva y absorción) y selecciona uno al azar,
 * devolviendo un evento con su tipo y probabilidad.
 * 
 * @param kdWeight Color que representa el peso de la reflexión difusa.
 * @param ksWeight Color que representa el peso de la reflexión especular.
 * @param ktWeight Color que representa el peso de la refracción.
 * @return RR_Event Estructura que contiene el tipo de evento seleccionado y su probabilidad.
 */
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

/**
 * @brief Genera un vector dispersado basado en el tipo de evento seleccionado por la ruleta rusa.
 * 
 * Dependiendo del tipo de evento (difusa, especular, refractiva o absorción), esta función calcula y devuelve un vector
 * que representa la dirección de la luz dispersada.
 * 
 * @param ray Rayo incidente que interactúa con el material.
 * @param intersection Información sobre la intersección del rayo con el material.
 * @param event Evento seleccionado por la ruleta rusa que determina el comportamiento del material.
 * @return Vector Dirección del rayo dispersado según el tipo de evento.
 */
Vector Material::getSacterredVector(const Ray &ray, const Intersection &intersection, const RR_Event event) const{
    switch (event.eventType){
        case DIFUSSE:
            return randomDirection(ray, intersection);
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

/**
 * @brief Constructor por defecto de la clase Material.
 * 
 * Este constructor inicializa un material con valores predeterminados para sus propiedades ópticas.
 * 
 * @param color Color que representa la reflexión difusa del material.
 */
Material::Material(const Color& color){
    this->kd = color;    
    this->ks = Color(0, 0, 0);
    this->kt = Color(0, 0, 0);
    this->ior = 0;
}

/**
 * @brief Constructor de la clase Material que inicializa las propiedades ópticas del material.
 * 
 * Este constructor permite crear un material con componentes de reflexión difusa (kd), especular (ks),
 * refractiva (kt) y un índice de refracción (ior) especificados.
 * 
 * @param kd Color que representa la reflexión difusa del material.
 * @param ks Color que representa la reflexión especular del material.
 * @param kt Color que representa la refracción del material.
 * @param ior Índice de refracción del material.
 */
Material::Material(const Color& kd, const Color& ks, const Color& kt, double ior){
    this->kd = kd;    
    this->ks = ks;
    this->kt = kt;
    this->ior = ior;
}

/**
 * @brief Establece el color del material.
 * 
 * Este método permite cambiar el color de reflexión difusa del material a un nuevo valor.
 * 
 * @param color Nuevo color que se asignará al material.
 */
void Material::setColor(const Color& color){
    this->color = color;
}

/**
 * @brief Genera una dirección aleatoria para la dispersión de luz en un material difuso.
 * 
 * Esta función calcula una dirección aleatoria en el espacio tridimensional, teniendo en cuenta la normal
 * en el punto de intersección y asegurando que la dirección generada sea ortogonal a la normal del material.
 * 
 * @param ray Rayo incidente que interactúa con el material.
 * @param intersection Información sobre la intersección del rayo con el material.
 * @return Vector Dirección aleatoria generada para la dispersión de luz.
 */
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

/**
 * @brief Calcula la iluminación directa en un punto de intersección utilizando el método de eventos siguientes.
 * 
 * Este método evalúa la contribución de cada fuente de luz a la iluminación del punto de intersección,
 * considerando si hay sombras y aplicando las funciones BRDF y BSDF correspondientes.
 * 
 * @param lights Lista de fuentes de luz en la escena.
 * @param intersection Información sobre la intersección del rayo con el material.
 * @param scene Escena que contiene las figuras intersectables.
 * @return Color Resultado de la iluminación directa en el punto de intersección.
 */
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

/**
 * @brief Calcula el color resultante de un material en un punto de intersección dado, considerando la iluminación directa e indirecta.
 * 
 * Este método implementa el algoritmo de trazado de rayos para calcular el color final en un punto de intersección,
 * utilizando la ruleta rusa para decidir si se absorbe, refleja o refracta la luz, y recursivamente calcula la iluminación indirecta.
 * 
 * @param ray Rayo incidente que interactúa con el material.
 * @param intersection Información sobre la intersección del rayo con el material.
 * @param lights Lista de fuentes de luz en la escena.
 * @param scene Escena que contiene las figuras intersectables.
 * @param depth Profundidad actual del rayo en el trazado (para evitar recursión infinita).
 * @return Color Resultado del color calculado en el punto de intersección.
 */
Color Material::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth) const{
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
            luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, depth+1);            
        }
        
        final += luzDirecta + (luzIndirecta * bsdf(randomRay, intersection, event) ) ;
        
    }
    final /= double(MAX_PATHS);
    return final;
}

/**
 * @brief Calcula la función BRDF (Bidirectional Reflectance Distribution Function) para un material dado.
 * 
 * Esta función devuelve el valor de la BRDF del material, que es una medida de cómo se distribuye la luz reflejada
 * en diferentes direcciones en relación con la dirección de incidencia y la normal en el punto de intersección.
 * 
 * @param ray Rayo incidente que interactúa con el material.
 * @param intersection Información sobre la intersección del rayo con el material.
 * @return Color Valor de la BRDF del material.
 */
Color Material::brdf(const Ray& ray, const Intersection& intersection) const{
    return this->kd / M_PI;
}

/**
 * @brief Calcula la función BSDF (Bidirectional Scattering Distribution Function) para un material dado.
 * 
 * Esta función devuelve el valor de la BSDF del material, que es una medida de cómo se distribuye la luz
 * en diferentes direcciones en relación con la dirección de incidencia y la normal en el punto de intersección,
 * considerando el tipo de evento seleccionado por la ruleta rusa.
 * 
 * @param ray Rayo incidente que interactúa con el material.
 * @param intersection Información sobre la intersección del rayo con el material.
 * @param event Evento seleccionado por la ruleta rusa que determina el comportamiento del material.
 * @return Color Valor de la BSDF del material según el tipo de evento.
 */
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

