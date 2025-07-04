#ifndef FIGURECOLLECTION_HPP
#define FIGURECOLLECTION_HPP
#include "Figure.hpp"
#include <vector>
#include <memory>

class FigureCollection: public Figure{
private:
    std::vector<Figure*> figureList;
public:
    FigureCollection();
    //FigureCollection(Figure figureList, size_t size);
    FigureCollection(std::vector<Figure*> figureList);
    virtual ~FigureCollection();
    void add(Figure *figure);
    void deleteAll();
    size_t size();
    virtual bool isIntersectedBy(const Ray& ray, double tMin, double tMax, Intersection& intersection) const override;
    virtual void applyTransform(const Matrix& t) override;
    std::vector<Figure*>::iterator iterator();
    std::vector<Figure*>::iterator begin();
    std::vector<Figure*>::const_iterator begin() const;
    std::vector<Figure*>::iterator end();
    std::vector<Figure*>::const_iterator end() const;
};

#endif /* FIGURECOLLECTION_HPP */