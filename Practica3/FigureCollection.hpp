#ifndef FIGURECOLLECTION_HPP
#define FIGURECOLLECTION_HPP
#include "Figure.hpp"
#include <vector>
#include <memory>

class FigureCollection: public Figure{
private:
    std::vector<std::shared_ptr<Figure>> figureList;
public:
    FigureCollection();
    //FigureCollection(Figure figureList, size_t size);
    FigureCollection(std::vector<std::shared_ptr<Figure>> figureList);
    ~FigureCollection();
    void add(const Figure& figure);
    void deleteAll();
    size_t size();
    std::vector<std::shared_ptr<Figure>>::iterator iterator();
    virtual bool isIntersectedBy(const Ray& ray) const;
};

#endif /* FIGURECOLLECTION_HPP */