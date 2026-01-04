/**
 * @file Material.cpp
 * @brief Implementacion de la clase Material y funciones relacionadas para el cálculo de la dispersion de la luz en un motor de renderizado basado en trayectorias.
 *
 * Este archivo contiene la logica para la simulacion de materiales, incluyendo la seleccion de eventos mediante ruleta rusa,
 * la generacion de vectores dispersados, el cálculo de la iluminacion directa e indirecta, y la evaluacion de las funciones BRDF y BSDF.
 *
 * @author Alex
 * @date 18-6-2025
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include "Material.hpp"
#include "Utils.hpp"

/**
 * @brief Funcion que implementa la ruleta rusa para seleccionar un evento de dispersion basado en las propiedades del material.
 *
 * Esta funcion calcula la probabilidad de cada tipo de evento (difusa, especular, refractiva y absorcion) y selecciona uno al azar,
 * devolviendo un evento con su tipo y probabilidad.
 *
 * @param kdWeight Color que representa el peso de la reflexion difusa.
 * @param ksWeight Color que representa el peso de la reflexion especular.
 * @param ktWeight Color que representa el peso de la refraccion.
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
 * @brief Funcion que implementa la ruleta rusa para seleccionar un evento de dispersion basado en las propiedades del material.
 *
 * Esta funcion calcula la probabilidad de cada tipo de evento (difusa, especular, refractiva y absorcion) y selecciona uno al azar,
 * devolviendo un evento con su tipo y probabilidad.
 *
 * @param material Material cuyas propiedades se utilizaran para la seleccion del evento.
 * @return RR_Event Estructura que contiene el tipo de evento seleccionado y su probabilidad.
 */
RR_Event russianRoulette(Material& material){
    return russianRoulette(material.kd, material.ks, material.kt);
}

/**
 * @brief Establece la emision del material.
 *
 * Este metodo permite cambiar el color de emision del material a un nuevo valor.
 *
 * @param emission Nuevo color de emision que se asignará al material.
 */
void Material::setEmission(const Color &emission)
{
    this->emission = emission;
}

/**
 * @brief Genera un vector dispersado basado en el tipo de evento seleccionado por la ruleta rusa.
 *
 * Dependiendo del tipo de evento (difusa, especular, refractiva o absorcion), esta funcion calcula y devuelve un vector
 * que representa la direccion de la luz dispersada.
 *
 * @param ray Rayo incidente que interactua con el material.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @param event Evento seleccionado por la ruleta rusa que determina el comportamiento del material.
 * @return Vector Direccion del rayo dispersado segun el tipo de evento.
 */
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

/**
 * @brief Constructor por defecto de la clase Material.
 *
 * Este constructor inicializa un material con valores predeterminados para sus propiedades opticas.
 *
 * @param color Color que representa la reflexion difusa del material.
 */
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

/**
 * @brief Constructor de la clase Material que inicializa las propiedades opticas del material.
 *
 * Este constructor permite crear un material con componentes de reflexion difusa (kd), especular (ks),
 * refractiva (kt) y un indice de refraccion (ior) especificados.
 *
 * @param kd Color que representa la reflexion difusa del material.
 * @param ks Color que representa la reflexion especular del material.
 * @param kt Color que representa la refraccion del material.
 * @param ior indice de refraccion del material.
 */
void Material::setColor(const Color& color){
    this->color = color;
}

/**
 * @brief Calcula la iluminacion directa del material utilizando el metodo de next event estimation.
 *
 * Este metodo evalua la contribucion de cada fuente de luz en la escena, considerando sombras y la BRDF del material,
 * para calcular el color resultante de la iluminacion directa en el punto de interseccion.
 *
 * @param lights Vector de punteros compartidos a las luces presentes en la escena.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @param scene Referencia a la coleccion de figuras que componen la escena.
 * @return Color Color resultante de la iluminacion directa en el punto de interseccion.
 */
Color Material::nextEvent(const std::vector<std::shared_ptr<Light>>& lights, const Intersection& intersection, const IntersectableFigure& scene) const{
    if (maxComponent(emission) > 0.0){
        return emission;
    }
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
 * @brief Calcula la iluminacion en un punto de interseccion utilizando fotones cercanos.
 *
 * Este metodo evalua la contribucion de los fotones almacenados en el mapa de fotones
 * que estan cerca del punto de interseccion, aplicando un nucleo de suavizado para calcular
 * el color resultante de la iluminacion indirecta.
 *
 * @param nearestPhotons Vector de punteros a los fotones cercanos al punto de interseccion.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @return Color Color resultante de la iluminacion indirecta en el punto de interseccion.
 */
Color Material::calculateIllumination(const std::vector<const Photon*>& nearestPhotons, const Intersection& intersection) const {
    Color result(0, 0, 0);
    int numPhotons = nearestPhotons.size();

    double r = -1;
    if (numPhotons > 0) {
        // Calcula el radio promedio de los fotones
        for (const Photon* photon : nearestPhotons) {
            double distance = module(photon->getPosition() - intersection.intersectionPoint);
            if (distance > r) {
                r = distance;
            }
        }
    }

    for (const Photon* photon : nearestPhotons) {
            // Asumimos que brdf necesita un rayo; aquí usamos un rayo con dirección dummy
            // Asegúrate de que la dirección sea consistente con cómo se esperan los argumentos de brdf
            /*
            Vector incoming = normalize(intersection.intersectionPoint - photon->getPosition());
            Ray incomingRay(photon->getPosition(), incoming);
            Color photonContribution = photon->getFlux() /(M_PI * r * r);
            
            */
           
            double dist = module(photon->getPosition() - intersection.intersectionPoint);
            double alpha = 0.918;
            double beta = 1.953;
            double u = 1 - std::exp(-beta * (dist * dist) / (2 * r * r));
            double d = 1 - std::exp(-beta);
            double kernelWeight = alpha * (1 - (u / d));
            //Vector incoming = normalize(intersection.intersectionPoint - photon->getPosition());
            //Ray incomingRay(photon->getPosition(), incoming);
            
            Color photonContribution = photon->getFlux() * kernelWeight;
            result += photonContribution;
    }

    return result / (M_PI * r * r);
}

/**
 * @brief Verifica si el material es emisivo.
 *
 * Este metodo comprueba si el material tiene una componente de emision mayor que cero,
 * lo que indica que el material emite luz por si mismo.
 *
 * @return bool True si el material es emisivo, false en caso contrario.
 */
bool Material::isEmissive() const{
    return maxComponent(this->emission) > 0.0;
}

/**
 * @brief Calcula el color resultante de un material en un punto de interseccion dado, considerando la iluminacion directa e indirecta.
 *
 * Este metodo implementa el algoritmo de trazado de rayos para calcular el color final en un punto de interseccion,
 * utilizando la ruleta rusa para decidir si se absorbe, refleja o refracta la luz, y recursivamente calcula la iluminacion indirecta.
 *
 * @param ray Rayo incidente que interactua con el material.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @param lights Lista de fuentes de luz en la escena.
 * @param scene Escena que contiene las figuras intersectables.
 * @param depth Profundidad actual del rayo en el trazado (para evitar recursion infinita).
 * @return Color Resultado del color calculado en el punto de interseccion.
 */
Color Material::getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth) const{
    
    if (depth >= settings.MAX_BOUNCES){
        //auto nearestPhotons = search_nearest(photonMap, intersection.intersectionPoint, 50, 0.1); // 50 fotones y radio de 0.1
        //return calculateIllumination(nearestPhotons, intersection);
        return Color(0, 0, 0); // Caso base de recursión
    } 

    if (maxComponent(emission) > 0.0){
        return emission;
    }
    Color final(0,0,0);
    //Color luzDirecta = this->nextEvent(lights, intersection, scene);
    
    for(int path = 0; path < settings.MAX_PATHS; path++){
        Color luzIndirecta(0,0,0);

        RR_Event event = russianRoulette(kd, ks, kt);
        
        if(event.eventType == ABSORTION){
            continue;
        }
        
        Intersection randomRayIntersection = intersection;
        Ray randomRay = ray;
        
        if(event.eventType != DIFUSSE){

            Vector randomVector = getSacterredVector(ray, intersection, event);
            Ray randomRay = Ray(intersection.intersectionPoint, randomVector);
            
            if (scene.isIntersectedBy(randomRay, 0.00001f, INT_MAX, randomRayIntersection)){
                luzIndirecta = randomRayIntersection.material->getColor(randomRay, randomRayIntersection, lights, scene, photonMap, depth + 1);
            }
           
        } else{
            auto nearestPhotons = search_nearest(photonMap, randomRayIntersection.intersectionPoint, settings.MAX_NEIGHBORS); // 50 fotones y radio de 0.1
            luzIndirecta = calculateIllumination(nearestPhotons, randomRayIntersection);
        }
        
        final += (luzIndirecta * bsdf(randomRay, intersection, event)) ;      
    }
    final /= double(settings.MAX_PATHS);
    return final;
}

/**
 * @brief Calcula la funcion de distribucion bidireccional de reflectancia (BRDF) para el material.
 *
 * Este metodo devuelve el valor de la BRDF del material en un punto de interseccion dado,
 * que describe como la luz es reflejada difusamente por la superficie del material.
 *
 * @param ray Rayo incidente que interactua con el material.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @return Color Valor de la BRDF en el punto de interseccion.
 */
Color Material::brdf(const Ray& ray, const Intersection& intersection) const{
    return this->kd / M_PI;
}

/**
 * @brief Calcula la funcion de distribucion bidireccional de dispersion (BSDF) para el material.
 *
 * Este metodo devuelve el valor de la BSDF del material en un punto de interseccion dado,
 * que describe como la luz es dispersada por la superficie del material segun el tipo de evento.
 *
 * @param ray Rayo incidente que interactua con el material.
 * @param intersection Informacion sobre la interseccion del rayo con el material.
 * @param event Evento seleccionado por la ruleta rusa que determina el comportamiento del material.
 * @return Color Valor de la BSDF en el punto de interseccion.
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
