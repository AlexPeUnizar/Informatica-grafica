/**
 * @file FigureCollection.cpp
 * @brief Implementacion de la clase FigureCollection para la gestion de colecciones de figuras geometricas.
 * 
 * Este archivo contiene la implementacion de los metodos de la clase FigureCollection, 
 * que permite almacenar, gestionar y operar sobre un conjunto de figuras geometricas, 
 * facilitando operaciones como la adicion, eliminacion y deteccion de intersecciones con rayos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "FigureCollection.hpp"
#include <stdlib.h>

/**
 * @brief Constructores de la clase FigureCollection.
 * 
 * Este bloque contiene las implementaciones de los constructores de la clase FigureCollection,
 * que permiten crear una coleccion vacia o inicializarla con una lista de figuras.
 */
FigureCollection::FigureCollection(){
    this->figureList = std::vector<Figure*>();
}

/**
 * @brief Constructor de la clase FigureCollection con una lista de figuras.
 * 
 * Crea una nueva coleccion de figuras geometricas a partir de un vector de punteros a figuras.
 * 
 * @param figureList Vector de punteros a objetos Figure que se añadirán a la coleccion.
 */
FigureCollection::FigureCollection(std::vector<Figure*> figureList){
    this->figureList = figureList;
}

/**
 * @brief Destructor de la clase FigureCollection.
 * 
 * Libera los recursos asociados con la coleccion de figuras, eliminando cada figura almacenada.
 */
FigureCollection::~FigureCollection(){
    figureList.clear();
}

/**
 * @brief Añade una figura a la coleccion.
 * 
 * Este metodo permite añadir un puntero a un objeto Figure a la coleccion de figuras.
 * 
 * @param figure Puntero al objeto Figure que se añadirá a la coleccion.
 */
void FigureCollection::add(Figure* figure){
    this->figureList.push_back(figure);
}

/**
 * @brief Elimina todas las figuras de la coleccion.
 * 
 * Este metodo limpia la lista de figuras, eliminando todas las referencias a los objetos Figure almacenados.
 */
void FigureCollection::deleteAll(){
    this->figureList.clear();
}

/**
 * @brief Devuelve el numero de figuras en la coleccion.
 * 
 * Este metodo retorna el tamaño actual de la coleccion de figuras, es decir, cuántas figuras están almacenadas.
 * 
 * @return Numero de figuras en la coleccion.
 */
size_t FigureCollection::size(){
    return this->figureList.size();
}

/**
 * @brief Devuelve un iterador para recorrer la coleccion de figuras.
 * 
 * Este metodo proporciona un iterador que permite recorrer la lista de figuras almacenadas en la coleccion.
 * 
 * @return Iterador para la lista de figuras.
 */
std::vector<Figure*>::iterator FigureCollection::iterator(){
    return this->figureList.begin();
}

/**
 * @brief Verifica si un rayo intersecta con alguna figura de la coleccion.
 * 
 * Este metodo recorre todas las figuras en la coleccion y verifica si el rayo intersecta con alguna de ellas,
 * actualizando el objeto Intersection con los detalles de la interseccion más cercana.
 * 
 * @param ray El rayo a verificar para la interseccion.
 * @param tMin El valor minimo de t para considerar la interseccion.
 * @param tMax El valor máximo de t para considerar la interseccion.
 * @param intersection Objeto Intersection donde se almacenarán los detalles de la interseccion si ocurre.
 * @return true Si al menos una figura es intersectada por el rayo, false en caso contrario.
 */
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

/**
 * @brief Aplica una transformacion matricial a todas las figuras de la coleccion.
 * 
 * Este metodo recorre todas las figuras en la coleccion y aplica la matriz de transformacion proporcionada a cada una.
 * 
 * @param t Matriz de transformacion a aplicar. 
 */
void FigureCollection::applyTransform(const Matrix& t) {
    for (auto& figure : figureList) {
        figure->applyTransform(t);
    }
}

/**
 * @brief Metodos para obtener iteradores de la coleccion de figuras.
 * 
 * Estos metodos permiten obtener iteradores para recorrer la coleccion de figuras, tanto en modo mutable como constante.
 */
std::vector<Figure*>::iterator FigureCollection::begin(){
    return this->figureList.begin();    
}

/**
 * @brief Metodo para obtener un iterador constante al inicio de la coleccion de figuras.
 * 
 * Este metodo permite obtener un iterador constante que apunta al primer elemento de la coleccion de figuras.
 * 
 * @return Iterador constante al inicio de la coleccion.
 */
std::vector<Figure*>::const_iterator FigureCollection::begin() const{
    return this->figureList.begin();    
}

/**
 * @brief Metodos para obtener iteradores al final de la coleccion de figuras.
 * 
 * Estos metodos permiten obtener iteradores que apuntan al final de la coleccion de figuras, tanto en modo mutable como constante.
 */
std::vector<Figure*>::iterator FigureCollection::end(){
    return this->figureList.end();    
}

/**
 * @brief Metodo para obtener un iterador constante al final de la coleccion de figuras.
 * 
 * Este metodo permite obtener un iterador constante que apunta al final de la coleccion de figuras.
 * 
 * @return Iterador constante al final de la coleccion.
 */
std::vector<Figure*>::const_iterator FigureCollection::end() const{
    return this->figureList.end();    
}
