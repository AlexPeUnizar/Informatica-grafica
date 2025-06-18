/**
 * @file Camera.cpp
 * @brief Implementación de la clase Camera para renderizado por ray tracing.
 *
 * Este archivo contiene la implementación de la clase Camera, responsable de
 * generar rayos a través de los píxeles, gestionar la orientación y posición de la cámara,
 * y renderizar una escena usando ray tracing. El proceso de renderizado soporta multihilo
 * para mejorar el rendimiento.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include <future>
#include <thread>
#include "Camera.hpp"
#include "Utils.hpp"
#include "progressbar.hpp"
#include "ThreadPool.hpp"

/**
 * @brief Constructores de la clase Camera.
 * 
 * Inicializa una nueva instancia de la clase Camera con los vectores de orientación
 * (up, left, front) y el punto de origen (o) especificados.
 * 
 * @param up    Vector que representa la dirección "arriba" de la cámara.
 * @param left  Vector que representa la dirección "izquierda" de la cámara.
 * @param front Vector que representa la dirección "frontal" de la cámara.
 * @param o     Punto de origen (posición) de la cámara.
 */
Camera::Camera(const Vector& up,const Vector& left,const Vector& front,const Point& o){
    this->up = up;
    this->left = left;
    this->front = front;
    this->o = o;
}

/**
 * @brief Destructor de la clase Camera.
 * 
 * Libera los recursos utilizados por la cámara, incluyendo los vectores de orientación
 * y el punto de origen.
 */
Camera::~Camera(){
    this->up.~Vector();    
    this->left.~Vector();    
    this->front.~Vector();    
    this->o.~Point();    
}

/**
 * @brief Obtiene el vector de dirección "arriba" de la cámara.
 * 
 * @return Referencia al vector "up" de la cámara.
 */
Vector& Camera::getUp(){
    return this->up;
}   

/**
 * @brief Obtiene el vector de dirección "izquierda" de la cámara.
 * 
 * @return Referencia al vector "left" de la cámara.
 */
Vector& Camera::getLeft(){
    return this->left;
}   

/**
 * @brief Obtiene el vector de dirección "frontal" de la cámara.
 * 
 * @return Referencia al vector "front" de la cámara.
 */
Vector& Camera::getFront(){
    return this->front;
}   

/**
 * @brief Obtiene el punto de origen (posición) de la cámara.
 * 
 * @return Referencia al punto de origen (o) de la cámara.
 */
Point& Camera::getO(){
    return this->o;
}   

/**
 * @brief Obtiene la altura de la cámara.
 * 
 * @return Referencia a la variable que almacena la altura de la cámara.
 */
size_t& Camera::getHeight(){
    return this->height;
}   

/**
 * @brief Obtiene el ancho de la cámara.
 * 
 * @return Referencia a la variable que almacena el ancho de la cámara.
 */
size_t& Camera::getWidth(){
    return this->width;
}

/**
 * @brief Establece la altura de la cámara.
 * 
 * @param height Nuevo valor para la altura de la cámara.
 */
void Camera::setHeight(const size_t height){
    this->height = height;     
}    

/**
 * @brief Establece el ancho de la cámara.
 * 
 * @param width Nuevo valor para el ancho de la cámara.
 */
void Camera::setWidth(const size_t width){
    this->width = width; 
}

/**
 * @brief Genera un rayo desde la cámara hacia un píxel específico de la imagen.
 * 
 * Calcula un rayo que apunta desde el origen de la cámara hacia un píxel
 * en las coordenadas (x, y) especificadas. El rayo se ajusta para incluir
 * una pequeña variación aleatoria dentro del píxel.
 * 
 * @param x Coordenada horizontal del píxel.
 * @param y Coordenada vertical del píxel.
 * @return Ray Un rayo que apunta al píxel especificado.
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
 * Recorre cada píxel de la imagen y genera un rayo hacia ese píxel. Luego, verifica
 * si el rayo intersecta con algún objeto en la escena. Si hay una intersección, calcula
 * el color del píxel basado en el material del objeto y las luces presentes en la escena.
 * 
 * @param scene Referencia a la colección de figuras que componen la escena.
 * @param lights Vector de punteros compartidos a las luces presentes en la escena.
 * @return PPM Imagen renderizada en formato PPM.
 */
PPM Camera::render(FigureCollection& scene, std::vector<std::shared_ptr<Light>>& lights){
    PPM image(this->height, this->width);
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

            for(size_t i = 0; i < MAX_RAYS_PER_PIXEL; i++){
                                
                Ray ray = this->getRayToPixel(x, y);
                
                Intersection intersection = Intersection();
                
                if(scene.isIntersectedBy(ray, 0.00001f, INT_MAX, intersection)){
                    color += intersection.material->getColor(ray, intersection, lights, scene);
                }
            }

            color /= double(MAX_RAYS_PER_PIXEL);
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
