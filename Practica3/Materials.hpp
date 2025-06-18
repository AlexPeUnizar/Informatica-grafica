/**
 * @file Materials.hpp
 * @brief Declaración de materiales para el sistema de renderizado, incluyendo modelos Lambertiano y Metálico.
 * 
 * Este archivo define las clases de materiales que pueden ser utilizados en el motor de gráficos,
 * proporcionando interfaces para el cálculo del color y la función BRDF de cada material.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef MATERIALS_HPP
#define MATERIALS_HPP
#include "Material.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"

/** 
 * @namespace Materials
 * @brief Espacio de nombres que agrupa las clases de materiales utilizados en el sistema de renderizado.
 * 
 * Este espacio de nombres contiene implementaciones específicas de materiales como Lambertiano y Metálico,
 * cada uno con sus propias propiedades y métodos para calcular la interacción con la luz.
 */
namespace Materials{
    /**
     * @class Lambertian
     * @brief Clase que representa un material con reflexión difusa (Lambertiano).
     * 
     * Este material simula la reflexión difusa de la luz, donde la luz se dispersa uniformemente en todas las direcciones.
     * Implementa el modelo BRDF de Lambert y calcula el color resultante en un punto de intersección.
     */
    class Lambertian: public Material{
    private:
        Color kd = Color(1,1,1);
    public:
        Lambertian() = default;
        Lambertian(const Color& color);
        Lambertian(double r, double g, double b);
        ~Lambertian() = default;
        virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& light, const IntersectableFigure& scene, int depth = 0) const override;
        virtual Color brdf(const Ray& ray, const Intersection& intersection) const ;
    };

    /**
     * @class Metal
     * @brief Clase que representa un material metálico con reflexión especular.
     * 
     * Este material simula la reflexión especular de la luz, donde la luz se refleja en una dirección específica,
     * similar a cómo lo haría un espejo. Implementa el modelo BRDF para metales y calcula el color resultante en un punto de intersección.
     */
    class Metal: public Material{
    private:
        Color kd = Color(1,1,1);
    public:
        Metal() = default;
        Metal(const Color& color);
        Metal(double r, double g, double b);
        ~Metal() = default;
        virtual Color getColor(const Ray& ray, const Intersection& intersection, const std::vector<std::shared_ptr<Light>>& light, const IntersectableFigure& scene, int depth = 0) const override;
        virtual Color brdf(const Ray& ray, const Intersection& intersection) const ;
    };

} // namespace Materials
#endif /* MATERIALS_HPP */