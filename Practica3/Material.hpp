#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <vector>
#include <memory>
#include "IntersectableFigure.hpp"
#include "Light.hpp"

const int MAX_BOUNCES = 6;
const int MAX_PATHS = 1;

class Intersection;
class IntersectableFigure;

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
    //virtual Color bsdf(const Ray& ray, const Intersection& intersection) const = 0;

    Color computeDifusse(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth = 0)const;
    Color computeSpecular(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth = 0)const;
    Color computeRefractive(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& lights, const IntersectableFigure& scene, int depth = 0)const;
    double computeRussianRoulette() const;
    double fresnelSchlick(double cosTheta, double ior);

};


#endif /* MATERIAL_HPP */