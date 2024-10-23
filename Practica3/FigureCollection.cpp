#include "FigureCollection.hpp"
#if 0
FigureCollection::FigureCollection(){
    this->figureList = std::vector<std::shared_ptr<Figure>>();
}
/*
FigureCollection::FigureCollection(Figure figureList[], size_t size){
    this->figureList = std::vector<std::shared_ptr<Figure>>();
    for (size_t i = 0; i < size; i++){
        this->figureList.push_back(std::make_shared<Figure>(figureList[i]));
    }
}
*/

FigureCollection::FigureCollection(std::vector<std::shared_ptr<Figure>> figureList){
    this->figureList = figureList;
}

FigureCollection::~FigureCollection(){
    this->figureList.clear();
}

void FigureCollection::add(const Figure& figure){
    this->figureList.push_back(std::make_shared<Figure>(figure));
}

void FigureCollection::deleteAll(){
    this->figureList.clear();
}

size_t FigureCollection::size(){
    return this->figureList.size();
}

std::vector<std::shared_ptr<Figure>>::iterator FigureCollection::iterator(){
    return this->figureList.begin();
}

bool FigureCollection::isIntersectedBy(const Ray& ray) const{
    for(std::shared_ptr<Figure> figure: this->figureList){
        if (figure.get()->isIntersectedBy(ray)){
            return true;
        }
    }
    return false;
}
#endif