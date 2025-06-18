/**
 * @file Material.hpp
 * @brief Declaraciones relacionadas con los materiales y su interacción con la luz en el sistema de trazado de rayos.
 *
 * Este archivo define la clase Material y estructuras asociadas para gestionar las propiedades ópticas de los materiales,
 * incluyendo la reflexión difusa, especular y refractiva, así como la implementación de la ruleta rusa para la selección
 * de eventos de dispersión. Proporciona interfaces para calcular el color resultante de la interacción de los rayos con
 * los materiales y la escena.
 *
 * @author Alex
 * @date 18-6-2025
 */
#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <vector>
#include <memory>
#include "IntersectableFigure.hpp"
#include "Light.hpp"
#include "Utils.hpp"

class Intersection;
class IntersectableFigure;

/* RUSSIAN ROULETTE */
/**
 * @enum RR_EventType
 * @brief Tipos de eventos para la ruleta rusa en el trazado de rayos.
 *
 * Define los tipos de eventos que pueden ocurrir durante el proceso de trazado de rayos,
 * incluyendo difusión, reflexión especular, refracción y absorción.
 */
enum RR_EventType{
    DIFUSSE,
    SPECULAR,
    REFRACTIVE,
    ABSORTION
};

/**
 * @struct RR_Event
 * @brief Estructura que representa un evento de ruleta rusa.
 *
 * Contiene el tipo de evento y su probabilidad asociada, utilizada para determinar el comportamiento
 * del material al interactuar con la luz durante el trazado de rayos.
 */
struct RR_Event{
    RR_EventType eventType;
    double probability;
};

/* FUNCTIONS */

RR_Event russianRoulette(Color kdWeight, Color ksWeight, Color ktWeight);

/**
 * @class Material
 * @brief Clase que representa las propiedades ópticas de un material en el sistema de trazado de rayos.
 *
 * Esta clase define las propiedades de un material, incluyendo su color difuso (kd), especular (ks),
 * refractivo (kt) y su índice de refracción (ior). Proporciona métodos para calcular la dirección
 * aleatoria de dispersión, el color resultante de la interacción con la luz y la implementación
 * de la ruleta rusa para seleccionar eventos de dispersión.
 */
class Material{
private:
    Color kd;
    Color ks;
    Color kt;
    double ior;
protected:
    Color color;
public:
    Material() = default;
    Material(const Color& color);
    Material(const Color& kd, const Color& ks, const Color& kt, double ior);
    ~Material() = default;
    void setColor(const Color& color);
    Vector randomDirection(const Ray& ray, const Intersection& intersection) const;
    virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth = 0) const;
    virtual Color brdf(const Ray& ray, const Intersection& intersection) const;
    Color nextEvent(const std::vector<std::shared_ptr<Light>>& lights, const Intersection& intersection, const IntersectableFigure& scene) const;
    Vector getSacterredVector(const Ray &ray, const Intersection &intersection, const RR_Event event) const;
    Color bsdf(const Ray& ray, const Intersection& intersection, const RR_Event event) const;
};

#endif /* MATERIAL_HPP */