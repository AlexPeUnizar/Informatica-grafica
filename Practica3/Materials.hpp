#ifndef MATERIALS_HPP
#define MATERIALS_HPP
#include "Material.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"


namespace Materials{
    class Lambertian: public Material{
    private:
        double kd = 1.0;
    public:
        Lambertian() = default;
        Lambertian(const Color& color);
        Lambertian(double r, double g, double b);
        ~Lambertian() = default;
        virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& light, const IntersectableFigure& scene, int depth) const override;
        virtual Color brdf(const Ray& ray, const Intersection& intersection) const override;
    };

} // namespace Material
#endif /* MATERIALS_HPP */