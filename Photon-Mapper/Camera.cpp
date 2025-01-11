#define _USE_MATH_DEFINES
#include <future>
#include <thread>
#include "Camera.hpp"
#include "Utils.hpp"
#include "progressbar.hpp"
#include "ThreadPool.hpp"
#include <math.h>

const size_t MAX_RAYS_PER_PIXEL = 64;

Camera::Camera(const Vector& up,const Vector& left,const Vector& front,const Point& o){
    this->up = up;
    this->left = left;
    this->front = front;
    this->o = o;
}

Camera::~Camera(){
    this->up.~Vector();    
    this->left.~Vector();    
    this->front.~Vector();    
    this->o.~Point();    
}

Vector& Camera::getUp(){
    return this->up;
}   

Vector& Camera::getLeft(){
    return this->left;
}   

Vector& Camera::getFront(){
    return this->front;
}   

Point& Camera::getO(){
    return this->o;
}   

size_t& Camera::getHeight(){
    return this->height;
}   

size_t& Camera::getWidth(){
    return this->width;
}

void Camera::setHeight(const size_t height){
    this->height = height;     
}    

void Camera::setWidth(const size_t width){
    this->width = width; 
}

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

PPM Camera::render(const FigureCollection& scene, const std::vector<std::shared_ptr<Light>>& lights){
    PPM image(this->height, this->width);
    PhotonMap photonMap = generatePhotonMap(scene, lights, MAX_PHOTONS);
    #define th 1
    #if th
    const int numThreads = std::thread::hardware_concurrency();
    ThreadPool pool(numThreads);
    std::vector<std::future<void>> futures;
    #endif
    
    for (size_t y = 0; y < this->height; y++){
        for (size_t x = 0; x < this->width; x++){
            #if th
            futures.emplace_back(pool.enqueue([&, x, y]() {
            #endif
            Color color(0,0,0);

            for(size_t i = 0; i < MAX_RAYS_PER_PIXEL; i++){
                                
                Ray ray = this->getRayToPixel(x, y);
                
                Intersection intersection = Intersection();
                
                if(scene.isIntersectedBy(ray, 0.00001f, INT_MAX, intersection)){
                    color += intersection.material->getColor(ray, intersection, lights, scene, photonMap);
                }
            }

            color /= double(MAX_RAYS_PER_PIXEL);
            //std::cout<<"Final: "<<color.r<<" "<<color.g<<" "<<color.b<<" "<<std::endl;
            image[y][x] = std::make_shared<PPM::Pixel>(color);
            #if !th
            pb.update();
            #endif
            #if th                    
            }));
            #endif
        }
    }
    #if th
    for (auto &f : futures) {
        f.get();
    }
    #endif
    return image;
}

PhotonMap Camera::generatePhotonMap(const FigureCollection& scene, const std::vector<std::shared_ptr<Light>>& lights, size_t totalPhotons){
    std::list<Photon> photons;
    double totalPower = 0;
    for (const auto& light : lights) {
        totalPower += light->intensity();
    }

    for (const auto& light : lights) {
        size_t photonsPerLight = 4096 * (light->intensity()/totalPower);

        for (size_t i = 0; i < photonsPerLight; ++i) {
            Point origin = light->getCenter();
            Vector direction = randomDirection(); 
            double flux = 4 * M_PI * light->intensity() / photonsPerLight;

            Ray photonRay(origin, direction);
            Intersection intersection;
            size_t bounce = 0;
            while (bounce++ < MAX_BOUNCES && scene.isIntersectedBy(photonRay, 0.001, INT_MAX, intersection)) {
                photons.push_back(Photon(intersection.intersectionPoint, photonRay.dir, flux));

                // Dispersión difusa
                direction = randomDirection(intersection.intersectionPoint, intersection.normal);
                photonRay = Ray(intersection.intersectionPoint, direction);
            }
        }
    }

    return newPhotonMap(photons); 
}
