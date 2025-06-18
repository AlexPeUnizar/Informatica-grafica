/**
 * @file FigureCollection.hpp
 * @brief Declaración de la clase FigureCollection, que representa una colección de figuras geométricas.
 * 
 * Esta clase permite gestionar un conjunto de objetos de tipo Figure, proporcionando métodos para añadir,
 * eliminar y recorrer las figuras almacenadas. Además, implementa la interfaz para comprobar intersecciones
 * con un rayo, útil en aplicaciones de gráficos por computadora y trazado de rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#ifndef FIGURECOLLECTION_HPP
#define FIGURECOLLECTION_HPP
#include "Figure.hpp"
#include <vector>
#include <memory>

/**
 * @class FigureCollection
 * @brief Clase que representa una colección de figuras geométricas.
 * 
 * Esta clase hereda de Figure y permite almacenar múltiples objetos de tipo Figure,
 * proporcionando métodos para añadir, eliminar y verificar intersecciones con rayos.
 * 
 * @see Figure
 */
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
    std::vector<Figure*>::iterator iterator();
    std::vector<Figure*>::iterator begin();
    std::vector<Figure*>::const_iterator begin() const;
    std::vector<Figure*>::iterator end();
    std::vector<Figure*>::const_iterator end() const;
};

#endif /* FIGURECOLLECTION_HPP */