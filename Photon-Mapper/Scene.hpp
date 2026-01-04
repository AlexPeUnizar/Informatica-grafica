/**
 * @file Scene.hpp
 * @author Alex
 * @brief Declaracion de la estructura SceneData para representar una escena 3D.
 * @date 2026-01-04
 * 
 */
#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include "FigureCollection.hpp"
#include "Light.hpp"
#include "Camera.hpp"

/**
 * @brief Estructura SceneData que representa una escena 3D completa.
 * 
 * Esta estructura contiene la colección de figuras, las luces y la cámara
 * que definen una escena 3D para su renderizado.
 */
struct SceneData {
    // Dueño real de la memoria:
    std::vector<std::unique_ptr<Figure>> ownedFigures;
    
    // Lo que usa el render:
    FigureCollection figures;
    std::vector<std::shared_ptr<Light>> lights;
    Camera camera;

    SceneData(const Camera& cam) : figures(), lights(), camera(cam) {}
};

#endif /* SCENE_HPP */