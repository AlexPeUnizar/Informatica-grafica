/**
 * @file Scenes.cpp
 * @author Alex
 * @brief Implementacion de escenas para el motor de renderizado.
 * @date 2026-01-04
 * 
 */
#include "Scenes.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Material.hpp"
#include "Materials.hpp"
#include "TriangleMesh.hpp"

/**
 * @brief Construye la escena 1 con figuras y luces predefinidas.
 * 
 * @return SceneData Estructura que contiene los datos de la escena, incluyendo figuras, luces y camara.
 */
SceneData buildScene1() {
    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> down(-)-up(+)
        z -> front(-)-back(+)
    */

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);

    Camera cam(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    cam.setWidth(settings.IMAGE_WIDTH);
    cam.setHeight(settings.IMAGE_HEIGHT);

    SceneData scene(cam);

    Color gris = Color::fromRGB(211,211,211);
        
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(gris));


    //(0,255,255)(255,0,255)

    Sphere leftSphere(
        Point(-0.5, -0.7, 0.25),
        0.3,
        std::make_shared<Material>(
            Color(0.0, 0.7, 0.7),  // kd: Azul
            Color(0.3, 0.3, 0.3),  // ks: Moderada reflectividad
            Color(0.0, 0.0, 0.0),  // kt: Sin refraccion
            1.0                    // ior
        )
    );

    Sphere rightSphere(
        Point(0.5, -0.7, -0.25),
        0.3,
        std::make_shared<Material>(
            Color(0, 0.0, 0),  // kd: Sin difusa
            Color(0.1, 0.1, 0.1),  // ks: Baja reflectividad
            Color(0.9, 0.9, 0.9),  // kt: Alta transparencia
            1.5                    // ior (indice de refraccion)
        )
    );

    // Creamos figuras en heap (ownedFigures las mantiene vivas)
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(leftPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(rightPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(floorPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(ceilingPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(backPlane));

    scene.ownedFigures.emplace_back(std::make_unique<Sphere>(leftSphere));
    scene.ownedFigures.emplace_back(std::make_unique<Sphere>(rightSphere));

    // Enlazamos punteros a FigureCollection
    for (auto& f : scene.ownedFigures) {
        scene.figures.add(f.get());
    }

    // Luces
    Light light(Point(0, 0.7, 0), Color(1,1,1));

    scene.lights.push_back(std::make_shared<Light>(light));

    return scene;
}

/**
 * @brief Construye la escena 2 con figuras y luces predefinidas.
 * 
 * @return SceneData Estructura que contiene los datos de la escena, incluyendo figuras, luces y camara.
 */
SceneData buildScene2() {

    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> down(-)-up(+)
        z -> front(-)-back(+)
    */

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);

    Camera cam(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    cam.setWidth(settings.IMAGE_WIDTH);
    cam.setHeight(settings.IMAGE_HEIGHT);

    SceneData scene(cam);

    Color gris = Color::fromRGB(211,211,211);
        
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(gris));


    //(0,255,255)(255,0,255)

    Sphere leftSphere(
        Point(-0.5, -0.7, 0.25),
        0.3,
        std::make_shared<Material>(
            Color(0.0, 0.7, 0.7),  // kd: Azul
            Color(0.3, 0.3, 0.3),  // ks: Moderada reflectividad
            Color(0.0, 0.0, 0.0),  // kt: Sin refraccion
            1.0                    // ior
        )
    );

    Sphere rightSphere(
        Point(0.5, -0.7, -0.25),
        0.3,
        std::make_shared<Material>(
            Color(0, 0.0, 0),  // kd: Sin difusa
            Color(0.1, 0.1, 0.1),  // ks: Baja reflectividad
            Color(0.9, 0.9, 0.9),  // kt: Alta transparencia
            1.5                    // ior (indice de refraccion)
        )
    );

    // Creamos figuras en heap (ownedFigures las mantiene vivas)
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(leftPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(rightPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(floorPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(ceilingPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(backPlane));

    scene.ownedFigures.emplace_back(std::make_unique<Sphere>(leftSphere));
    scene.ownedFigures.emplace_back(std::make_unique<Sphere>(rightSphere));

    // Enlazamos punteros a FigureCollection
    for (auto& f : scene.ownedFigures) {
        scene.figures.add(f.get());
    }

    // Luces
    ceilingPlane.setEmission(Color(1,1,1));
    Light light(Point(0, 0.7, 0), Color(0,0,0));

    scene.lights.push_back(std::make_shared<Light>(light));

    return scene;
}

/**
 * @brief Construye la escena 3 con figuras y luces predefinidas.
 * 
 * @return SceneData Estructura que contiene los datos de la escena, incluyendo figuras, luces y camara.
 */
SceneData buildScene3() {
    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> down(-)-up(+)
        z -> front(-)-back(+)
    */

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);

    Camera cam(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    cam.setWidth(settings.IMAGE_WIDTH);
    cam.setHeight(settings.IMAGE_HEIGHT);

    SceneData scene(cam);

    Color gris = Color::fromRGB(211,211,211);
        
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(gris));


    //(0,255,255)(255,0,255)

    Sphere leftSphere(
        Point(-0.5, -0.7, 0.25),
        0.3,
        std::make_shared<Material>(Color::fromRGB(255,0,255))
    );
    
    Sphere rightSphere(
        Point(0.5, -0.7, -0.25),
        0.3,
        std::make_shared<Material>(Color::fromRGB(0,255,255))
    );

    // Creamos figuras en heap (ownedFigures las mantiene vivas)
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(leftPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(rightPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(floorPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(ceilingPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(backPlane));

    scene.ownedFigures.emplace_back(std::make_unique<Sphere>(leftSphere));
    scene.ownedFigures.emplace_back(std::make_unique<Sphere>(rightSphere));

    // Enlazamos punteros a FigureCollection
    for (auto& f : scene.ownedFigures) {
        scene.figures.add(f.get());
    }

    // Luces
    Light light(Point(0, 0.7, 0), Color(1,1,1));

    scene.lights.push_back(std::make_shared<Light>(light));

    return scene;
}

/**
 * @brief Construye la escena 4 con figuras y luces predefinidas.
 * 
 * @return SceneData Estructura que contiene los datos de la escena, incluyendo figuras, luces y camara.
 */
SceneData buildScene4() {
    /* FIGURES */
    /*
        x -> left(-)-right(+)
        y -> down(-)-up(+)
        z -> front(-)-back(+)
    */

    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);

    Camera cam(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    cam.setWidth(settings.IMAGE_WIDTH);
    cam.setHeight(settings.IMAGE_HEIGHT);

    SceneData scene(cam);

    Color gris = Color::fromRGB(211,211,211);
        
    Plane leftPlane(Vector(1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,0)));
    Plane rightPlane(Vector(-1, 0, 0), 1, std::make_shared<Materials::Lambertian>(Color::fromRGB(0,255,0)));
    Plane floorPlane(Vector(0, 1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane ceilingPlane(Vector(0, -1, 0), 1, std::make_shared<Materials::Lambertian>(gris));
    Plane backPlane(Vector(0, 0, -1), 1, std::make_shared<Materials::Lambertian>(gris));


    //(0,255,255)(255,0,255)

    auto mesh = TriangleMesh::fromOBJ(
        "models/bunny.obj",
        std::make_shared<Materials::Lambertian>(Color::fromRGB(255,0,255)),
        true, // smooth
        10.0, // scaleFactor
        Vector(0.2, -1.2, 0)
    );    

    // Creamos figuras en heap (ownedFigures las mantiene vivas)
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(leftPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(rightPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(floorPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(ceilingPlane));
    scene.ownedFigures.emplace_back(std::make_unique<Plane>(backPlane));

    //scene.ownedFigures.emplace_back(std::make_unique<Sphere>(leftSphere));
    //scene.ownedFigures.emplace_back(std::make_unique<Sphere>(rightSphere));
    scene.ownedFigures.emplace_back(std::move(mesh));

    // Enlazamos punteros a FigureCollection
    for (auto& f : scene.ownedFigures) {
        scene.figures.add(f.get());
    }

    // Luces
    Light light(Point(0, 0.7, 0), Color(1,1,1));

    scene.lights.push_back(std::make_shared<Light>(light));

    return scene;
}