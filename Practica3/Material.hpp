#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "IntersectableFigure.hpp"
#include "Light.hpp"

class Material{
private:
    /* data */
protected:
    Color color;
public:
    Material() = default;
    Material(const Color& color);
    ~Material() = default;
    virtual Color brdf(const Ray& ray, const Intersection& intersection, const Light& light) const = 0;
};
namespace Materials{

    
    class Difusse: public Material{
    private:
        /* data */
    public:
        Difusse() = default;
        Difusse(const Color& color);
        ~Difusse() = default;
        virtual Color brdf(const Ray& ray, const Intersection& intersection, const Light& light) const;
};

} // namespace Material

#endif /* MATERIAL_HPP */