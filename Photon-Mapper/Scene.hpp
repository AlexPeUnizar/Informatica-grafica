#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include "FigureCollection.hpp"
#include "Light.hpp"
#include "Camera.hpp"

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