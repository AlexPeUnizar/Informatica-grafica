#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <vector>
#include <memory>
#include "IntersectableFigure.hpp"
#include "Light.hpp"
#include "PhotonMap.hpp"

class Intersection;
class IntersectableFigure;

/* RUSSIAN ROULETTE */
enum RR_EventType{
    DIFUSSE,
    SPECULAR,
    REFRACTIVE,
    ABSORTION
};

struct RR_Event{
    RR_EventType eventType;
    double probability;
};

/* FUNCTIONS */
RR_Event russianRoulette(Color kdWeight, Color ksWeight, Color ktWeight);

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
    virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth = 0) const;
    virtual Color brdf(const Ray& ray, const Intersection& intersection) const;
    Color nextEvent(const std::vector<std::shared_ptr<Light>>& lights, const Intersection& intersection, const IntersectableFigure& scene) const;
    Vector getSacterredVector(const Ray &ray, const Intersection &intersection, const RR_Event event) const;
    Color bsdf(const Ray& ray, const Intersection& intersection, const RR_Event event) const;
    Color calculateIllumination(const std::vector<const Photon*>& nearestPhotons, const Intersection& intersection) const;
    friend RR_Event russianRoulette(Material& material);
};



#endif /* MATERIAL_HPP */