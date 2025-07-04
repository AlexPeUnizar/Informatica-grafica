#define _USE_MATH_DEFINES
#include <future>
#include <thread>
#include "Camera.hpp"
#include "Utils.hpp"
#include "progressbar.hpp"
#include "ThreadPool.hpp"
#include "ScopedTimer.hpp"
#include <math.h>

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
    PhotonMap photonMap;
    {
        ScopedTimer timer("PhotonMap Generation Timer");
        photonMap = generatePhotonMap(scene, lights, MAX_PHOTONS);
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


            while (bounce < MAX_BOUNCES && scene.isIntersectedBy(photonRay, 1e-6f, INT_MAX, intersection)) {
                RR_Event event = russianRoulette(*intersection.material);
                
                if(event.eventType == ABSORTION){
                    continue;
                }

                flux = flux * intersection.material->bsdf(photonRay, intersection, event);
                
                if(event.eventType == DIFUSSE){
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
