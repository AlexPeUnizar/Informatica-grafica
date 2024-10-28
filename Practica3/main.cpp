#include "PathTracing.hpp"

using namespace std;

int main(){
    srand(time(NULL));

    Plane leftPlane(Vector(1, 0, 0), 1);
    leftPlane.setColor(255,0,0);
    Plane rightPlane(Vector(-1, 0, 0), 1);
    rightPlane.setColor(0,255,0);
    Plane floorPlane(Vector(0, 1, 0), 1);
    floorPlane.setColor(211,211,211);
    Plane ceilingPlane(Vector(0, -1, 0), 1);
    ceilingPlane.setColor(211,211,211);
    Plane backPlane(Vector(0, 0, -1), 1);
    backPlane.setColor(211,211,211);

    Sphere leftSphere(Point(-0.5, -0.7, 0.25), 0.3);
    leftSphere.setColor(255,0,255);
    Sphere rightSphere(Point(0.5, -0.7, -0.25), 0.3);
    rightSphere.setColor(0,255,255);
    Sphere upSphere(Point(0, 0.7, -0), 0.3);
    upSphere.setColor(3,54,1);

    FigureCollection figures(vector<Figure*>(
        {&leftPlane, &rightPlane, &ceilingPlane, &floorPlane, &backPlane, &leftSphere, &rightSphere, &upSphere}
    ));
    
    //Camera 
    Point cameraOrigin(0,0, -3.5);
    Vector cameraLeftVector(-1, 0, 0);
    Vector cameraUpVector(0, 1, 0);
    Vector cameraForwardVector(0, 0, 3);
    size_t width = 256;
    size_t height = 256;
    Camera camera(cameraUpVector, cameraLeftVector, cameraForwardVector, cameraOrigin);
    camera.setHeight(height);
    camera.setWidth(width);

    PPM image(width, height);

    for (size_t y = 0; y < height; y++){
        for (size_t x = 0; x < width; x++){
            
            double r=0, g=0, b=0;

            for(int i = 0; i < MAX_RAYS_PER_PIXEL; i++){
                Ray ray = camera.getRayToPixel(x, y);

                Figure *closestFig = nullptr;
                double min = INT_MAX-1;
                IntersectableFigure::Intersection intersection = IntersectableFigure::Intersection();

                for(auto fig:figures){
                    if(fig->isIntersectedBy(ray, intersection)){
                        if(intersection.t < min){
                            closestFig = fig;
                            min = intersection.t;
                        }
                    }
                }
                r += closestFig->getR();
                g += closestFig->getG();
                b += closestFig->getB();
            }
            
            image[y][x] = std::make_shared<PPM::Pixel>(PPM::Pixel{
                (r/double(MAX_RAYS_PER_PIXEL))/255.0, 
                (g/double(MAX_RAYS_PER_PIXEL))/255.0, 
                (b/double(MAX_RAYS_PER_PIXEL))/255.0
            });
        }
    }

    image.save();
    cout << "Done." << endl;
    return 0;
}   

