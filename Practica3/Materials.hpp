#ifndef MATERIALS_HPP
#define MATERIALS_HPP
#include "Material.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"


namespace Materials{
    class Lambertian: public Material{
    private:
        double kd = 0.2;
    public:
        Lambertian() = default;
        Lambertian(const Color& color);
        Lambertian(double r, double g, double b);
        ~Lambertian() = default;
        virtual Color emission(const Ray& ray, const Intersection& intersection, const Light& light, const IntersectableFigure& scene) const override;
};

} // namespace Material
#endif /* MATERIALS_HPP */