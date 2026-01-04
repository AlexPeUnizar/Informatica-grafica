/**
 * @file Camera.cpp
 * @brief Implementacion de la clase Camera para renderizado por ray tracing.
 *
 * Este archivo contiene la implementacion de la clase Camera, responsable de
 * generar rayos a traves de los pixeles, gestionar la orientacion y posicion de la camara,
 * y renderizar una escena usando ray tracing. El proceso de renderizado soporta multihilo
 * para mejorar el rendimiento.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#define _USE_MATH_DEFINES
#include <future>
#include <thread>
#include "Camera.hpp"
#include "Utils.hpp"
#include "progressbar.hpp"
#include "ThreadPool.hpp"
#include "ScopedTimer.hpp"
#include <math.h>

/**
 * @brief Constructores de la clase Camera.
 * 
 * Inicializa una nueva instancia de la clase Camera con los vectores de orientacion
 * (up, left, front) y el punto de origen (o) especificados.
 * 
 * @param up    Vector que representa la direccion "arriba" de la camara.
 * @param left  Vector que representa la direccion "izquierda" de la camara.
 * @param front Vector que representa la direccion "frontal" de la camara.
 * @param o     Punto de origen (posicion) de la camara.
 */
Camera::Camera(const Vector& up,const Vector& left,const Vector& front,const Point& o){
    this->up = up;
    this->left = left;
    this->front = front;
    this->o = o;
}

/**
 * @brief Obtiene el vector de direccion "arriba" de la camara.
 * 
 * @return Referencia al vector "up" de la camara.
 */
Camera::~Camera(){
    this->up.~Vector();    
    this->left.~Vector();    
    this->front.~Vector();    
    this->o.~Point();    
}

Vector& Camera::getUp(){
    return this->up;
}   

/**
 * @brief Obtiene el vector de direccion "izquierda" de la camara.
 * 
 * @return Referencia al vector "left" de la camara.
 */
Vector& Camera::getLeft(){
    return this->left;
}   

/**
 * @brief Obtiene el vector de direccion "frontal" de la camara.
 * 
 * @return Referencia al vector "front" de la camara.
 */
Vector& Camera::getFront(){
    return this->front;
}   

/**
 * @brief Obtiene el punto de origen (posicion) de la camara.
 * 
 * @return Referencia al punto de origen (o) de la camara.
 */
Point& Camera::getO(){
    return this->o;
}   

/**
 * @brief Obtiene la altura de la camara.
 * 
 * @return Referencia a la variable que almacena la altura de la camara.
 */
size_t& Camera::getHeight(){
    return this->height;
}   

/**
 * @brief Obtiene el ancho de la camara.
 * 
 * @return Referencia a la variable que almacena el ancho de la camara.
 */
size_t& Camera::getWidth(){
    return this->width;
}

/**
 * @brief Establece la altura de la camara.
 * 
 * @param height Nuevo valor para la altura de la camara.
 */
void Camera::setHeight(const size_t height){
    this->height = height;     
}    

/**
 * @brief Establece el ancho de la camara.
 * 
 * @param width Nuevo valor para el ancho de la camara.
 */
void Camera::setWidth(const size_t width){
    this->width = width; 
}

/**
 * @brief Genera un rayo desde la camara hacia un pixel especifico de la imagen.
 * 
 * Calcula un rayo que apunta desde el origen de la camara hacia un pixel
 * en las coordenadas (x, y) especificadas. El rayo se ajusta para incluir
 * una pequeña variacion aleatoria dentro del pixel.
 * 
 * @param x Coordenada horizontal del pixel.
 * @param y Coordenada vertical del pixel.
 * @return Ray Un rayo que apunta al pixel especificado.
 */
Ray Camera::getRayToPixel(size_t x, size_t y){
    Vector upperLeft = this->front + this->left + this->up;

    Vector vectorToUpperCorner = upperLeft + 
                            this->left * -2 * (double(x)/double(this->width)) + 
                            this->up * -2 * (double(y)/double(this->height));
    Vector vectorToLowerCorner = upperLeft + 
                            this->left * -2 * (double(x+1)/double(this->width)) + 
                            this->up * -2 * (double(y+1)/double(this->height));

    Point upCorner = Ray(this->o, normalize(vectorToUpperCorner)).at(module(vectorToUpperCorner));
    Point downCorner = Ray(this->o, normalize(vectorToLowerCorner)).at(module(vectorToLowerCorner));

    Point p = Point(randomDouble(upCorner.x, downCorner.x), randomDouble(downCorner.y, upCorner.y), upCorner.z);
    Ray ray(this->o, p - this->o);
    
    return ray;
}

/**
 * @brief Renderiza una escena 3D utilizando ray tracing.
 * 
 * Recorre cada pixel de la imagen y genera un rayo hacia ese pixel. Luego, verifica
 * si el rayo intersecta con algun objeto en la escena. Si hay una interseccion, calcula
 * el color del pixel basado en el material del objeto y las luces presentes en la escena.
 * 
 * @param scene Referencia a la coleccion de figuras que componen la escena.
 * @param lights Vector de punteros compartidos a las luces presentes en la escena.
 * @return PPM Imagen renderizada en formato PPM.
 */
PPM Camera::render(const FigureCollection& scene, const std::vector<std::shared_ptr<Light>>& lights){
    PPM image(this->height, this->width);
    PhotonMap photonMap;
    {
        ScopedTimer timer("PhotonMap Generation Timer");
        photonMap = generatePhotonMap(scene, lights, settings.MAX_PHOTONS);
    }
    const int total = this->height * this->width;
    std::atomic<int> pixels_done{0};
    progressbar pb(this->height * this->width);
    
    const int numThreads = std::thread::hardware_concurrency();
    ThreadPool pool(numThreads);
    std::vector<std::future<void>> futures;

    std::thread reporter([&]() {
        while (true) {
            int done = pixels_done.load(std::memory_order_relaxed);
            if (done >= total) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            pb.setProgress(done, total);
        }
        // rematar al 100% y salto de línea
        pb.setProgress(total, total);
        pb.finish();  
    });

    for (size_t y = 0; y < this->height; y++){
        for (size_t x = 0; x < this->width; x++){
            futures.emplace_back(pool.enqueue([&, x, y]() {
            
            Color color(0,0,0);

            for(size_t i = 0; i < settings.MAX_RAYS_PER_PIXEL; i++){
                                
                Ray ray = this->getRayToPixel(x, y);
                
                Intersection intersection = Intersection();
                
                if(scene.isIntersectedBy(ray, 0.00001f, INT_MAX, intersection)){
                    color += intersection.material->getColor(ray, intersection, lights, scene, photonMap);
                }
            }

            color /= double(settings.MAX_RAYS_PER_PIXEL);
            //std::cout<<"Final: "<<color.r<<" "<<color.g<<" "<<color.b<<" "<<std::endl;
            image[y][x] = std::make_shared<PPM::Pixel>(color);
            pixels_done.fetch_add(1, std::memory_order_relaxed);
    
            }));
        }
    }
    reporter.join();
    for (auto &f : futures) {
        f.get();
    }
    return image;
}

/**
 * @brief Genera un mapa de fotones para la escena dada.
 * 
 * Simula la emision y dispersion de fotones desde las luces en la escena.
 * Los fotones se lanzan desde las luces en direcciones aleatorias y se
 * almacenan en el mapa de fotones cuando interactuan con superficies difusas.
 * 
 * @param scene Referencia a la coleccion de figuras que componen la escena.
 * @param lights Vector de punteros compartidos a las luces presentes en la escena.
 * @param totalPhotons Numero total de fotones a generar.
 * @return PhotonMap Mapa de fotones generado para la escena.
 */
PhotonMap Camera::generatePhotonMap(const FigureCollection& scene, const std::vector<std::shared_ptr<Light>>& lights, size_t totalPhotons){
    std::vector<Photon> photons;
    double totalPower = 0;
    for (const auto& light : lights) {
        totalPower += light->intensity();
    }
    for (const auto& light : lights) {
        size_t photonsPerLight = totalPhotons * (light->intensity()/totalPower);
        
        for (size_t i = 0; i < photonsPerLight; ++i) {
            Point origin = light->getCenter();
            Vector direction = randomDirection(); 
            Color flux = 4 * M_PI * light->getPower() / photonsPerLight;
            
            Ray photonRay(origin, direction);
            Intersection intersection;
            size_t bounce = 0;
            // Dispersión difusa
            //direction = randomDirection(intersection.intersectionPoint, intersection.normal);
            //photonRay = Ray(intersection.intersectionPoint, direction);


            while (bounce < settings.MAX_BOUNCES && scene.isIntersectedBy(photonRay, 1e-6f, INT_MAX, intersection)) {
                RR_Event event = russianRoulette(*intersection.material);
                
                if(event.eventType == ABSORTION){
                    continue;
                }

                flux = flux * intersection.material->bsdf(photonRay, intersection, event);
                
                if(event.eventType == DIFUSSE /*&& bounce > 1*/){
                    photons.push_back(Photon(intersection.intersectionPoint, photonRay.dir, flux));
                }
                bounce++;
                
                Vector randomVector = intersection.material->getSacterredVector(photonRay, intersection, event);
                photonRay = Ray(intersection.intersectionPoint, randomVector);
            }
        }
    }

    return newPhotonMap(photons); 
}
