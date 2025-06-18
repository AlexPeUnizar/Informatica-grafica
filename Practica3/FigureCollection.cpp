/**
 * @file FigureCollection.cpp
 * @brief Implementación de la clase FigureCollection para la gestión de colecciones de figuras geométricas.
 * 
 * Este archivo contiene la implementación de los métodos de la clase FigureCollection, 
 * que permite almacenar, gestionar y operar sobre un conjunto de figuras geométricas, 
 * facilitando operaciones como la adición, eliminación y detección de intersecciones con rayos.
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
 * que permiten crear una colección vacía o inicializarla con una lista de figuras.
 */
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

/**
 * @brief Constructor de la clase FigureCollection con una lista de figuras.
 * 
 * Crea una nueva colección de figuras geométricas a partir de un vector de punteros a figuras.
 * 
 * @param figureList Vector de punteros a objetos Figure que se añadirán a la colección.
 */
FigureCollection::FigureCollection(std::vector<Figure*> figureList){
    this->figureList = figureList;
}

/**
 * @brief Destructor de la clase FigureCollection.
 * 
 * Libera los recursos asociados con la colección de figuras, eliminando cada figura almacenada.
 */
FigureCollection::~FigureCollection(){
    for(size_t i = 0; i < figureList.size(); i++){
        figureList[i]->~Figure();
    }
    figureList.clear();
}

/**
 * @brief Añade una figura a la colección.
 * 
 * Este método permite añadir un puntero a un objeto Figure a la colección de figuras.
 * 
 * @param figure Puntero al objeto Figure que se añadirá a la colección.
 */
void FigureCollection::add(Figure* figure){
    this->figureList.push_back(figure);
}

/**
 * @brief Elimina todas las figuras de la colección.
 * 
 * Este método limpia la lista de figuras, eliminando todas las referencias a los objetos Figure almacenados.
 */
void FigureCollection::deleteAll(){
    this->figureList.clear();
}

/**
 * @brief Devuelve el número de figuras en la colección.
 * 
 * Este método retorna el tamaño actual de la colección de figuras, es decir, cuántas figuras están almacenadas.
 * 
 * @return Número de figuras en la colección.
 */
size_t FigureCollection::size(){
    return this->figureList.size();
}

/**
 * @brief Devuelve un iterador para recorrer la colección de figuras.
 * 
 * Este método proporciona un iterador que permite recorrer la lista de figuras almacenadas en la colección.
 * 
 * @return Iterador para la lista de figuras.
 */
std::vector<Figure*>::iterator FigureCollection::iterator(){
    return this->figureList.begin();
}

/**
 * @brief Verifica si un rayo intersecta con alguna figura de la colección.
 * 
 * Este método recorre todas las figuras en la colección y verifica si el rayo intersecta con alguna de ellas,
 * actualizando el objeto Intersection con los detalles de la intersección más cercana.
 * 
 * @param ray El rayo a verificar para la intersección.
 * @param tMin El valor mínimo de t para considerar la intersección.
 * @param tMax El valor máximo de t para considerar la intersección.
 * @param intersection Objeto Intersection donde se almacenarán los detalles de la intersección si ocurre.
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
 * @brief Métodos para obtener iteradores de la colección de figuras.
 * 
 * Estos métodos permiten obtener iteradores para recorrer la colección de figuras, tanto en modo mutable como constante.
 */
std::vector<Figure*>::iterator FigureCollection::begin(){
    return this->figureList.begin();    
}

/**
 * @brief Método para obtener un iterador constante al inicio de la colección de figuras.
 * 
 * Este método permite obtener un iterador constante que apunta al primer elemento de la colección de figuras.
 * 
 * @return Iterador constante al inicio de la colección.
 */
std::vector<Figure*>::const_iterator FigureCollection::begin() const{
    return this->figureList.begin();    
}

/**
 * @brief Métodos para obtener iteradores al final de la colección de figuras.
 * 
 * Estos métodos permiten obtener iteradores que apuntan al final de la colección de figuras, tanto en modo mutable como constante.
 */
std::vector<Figure*>::iterator FigureCollection::end(){
    return this->figureList.end();    
}

/**
 * @brief Método para obtener un iterador constante al final de la colección de figuras.
 * 
 * Este método permite obtener un iterador constante que apunta al final de la colección de figuras.
 * 
 * @return Iterador constante al final de la colección.
 */
std::vector<Figure*>::const_iterator FigureCollection::end() const{
    return this->figureList.end();    
}

