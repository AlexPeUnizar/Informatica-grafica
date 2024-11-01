#include "Material.hpp"

Material::Material(const Color& color){
    this->color = color;
}

Materials::Difusse::Difusse(const Color& color): Material(color){

}

Color Materials::Difusse::brdf(const Ray& ray, const Intersection& intersection, const Light& light) const{
    return Color(0,0,0);
}