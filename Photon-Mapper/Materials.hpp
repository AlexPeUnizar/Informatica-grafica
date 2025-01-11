#ifndef MATERIALS_HPP
#define MATERIALS_HPP
#include "Material.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"

namespace Materials{

    class Lambertian: public Material{
    private:
        Color kd = Color(1,1,1);
    public:
        Lambertian() = default;
        Lambertian(const Color& color);
        Lambertian(double r, double g, double b);
        ~Lambertian() = default;
        virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& light, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth = 0) const override;
        virtual Color brdf(const Ray& ray, const Intersection& intersection) const ;
    };

    class Metal: public Material{
    private:
        Color kd = Color(1,1,1);
    public:
        Metal() = default;
        Metal(const Color& color);
        Metal(double r, double g, double b);
        ~Metal() = default;
        virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& light, const IntersectableFigure& scene, const PhotonMap& photonMap, int depth = 0) const override;
        virtual Color brdf(const Ray& ray, const Intersection& intersection) const ;
    };

} // namespace Materials
#endif /* MATERIALS_HPP */