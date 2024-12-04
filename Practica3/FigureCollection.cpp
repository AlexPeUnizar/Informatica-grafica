#include "FigureCollection.hpp"
#include <stdlib.h>

FigureCollection::FigureCollection(){
    this->figureList = std::vector<Figure*>();
}
/*
FigureCollection::FigureCollection(Figure figureList[], size_t size){
    this->figureList = std::vector<std::shared_ptr<Figure>>();
    for (size_t i = 0; i < size; i++){
        this->figureList.push_back(std::make_shared<Figure>(figureList[i]));
    }
}
*/

FigureCollection::FigureCollection(std::vector<Figure*> figureList){
    this->figureList = figureList;
}

FigureCollection::~FigureCollection(){
    for(size_t i = 0; i < figureList.size(); i++){
        figureList[i]->~Figure();
    }
    figureList.clear();
}

void FigureCollection::add(Figure* figure){
    this->figureList.push_back(figure);
}

void FigureCollection::deleteAll(){
    this->figureList.clear();
}

size_t FigureCollection::size(){
    return this->figureList.size();
}

std::vector<Figure*>::iterator FigureCollection::iterator(){
    return this->figureList.begin();
}

bool FigureCollection::isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const{
    Intersection tmp;
    bool anyHit = false;
    double closest = tMax;

    for (const auto& fig : this->figureList) {
        if (fig->isIntersectedBy(ray, tMin, closest, tmp)) {
            anyHit = true;
            closest = tmp.t;
            intersection = tmp;
        }
    }

    return anyHit;      
}

std::vector<Figure*>::iterator FigureCollection::begin(){
    return this->figureList.begin();    
}

std::vector<Figure*>::const_iterator FigureCollection::begin() const{
    return this->figureList.begin();    
}

std::vector<Figure*>::iterator FigureCollection::end(){
    return this->figureList.end();    
}

std::vector<Figure*>::const_iterator FigureCollection::end() const{
    return this->figureList.end();    
}

