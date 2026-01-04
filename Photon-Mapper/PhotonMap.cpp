/**
 * @file PhotonMap.cpp
 * @brief Implementacion del mapa de fotones utilizando un KDTree para el almacenamiento y busqueda eficiente.
 * 
 * Este archivo contiene la definicion de las funciones relacionadas con el mapa de fotones,
 * incluyendo la creacion del mapa y la busqueda de fotones cercanos.
 * 
 * @author Alex
 * @date 18-6-2025
 */
#include "PhotonMap.hpp"

/**
 * @brief Constructor de la clase Photon.
 * 
 * Crea un nuevo objeto Photon con la posicion, incidente y flujo especificados.
 * 
 * @param pos Punto que representa la posicion del foton.
 * @param incident Vector que representa la direccion incidente del foton.
 * @param flux Color que representa el flujo de energia del foton.
 */
Photon::Photon(const Point &pos, const Vector& incident, const Color& flux){
    this->pos = pos;    
    this->incident = incident;    
    this->flux = flux;    
}

/**
 * @brief Crea un nuevo mapa de fotones a partir de una lista de fotones.
 * 
 * Esta funcion inicializa un KDTree con los fotones proporcionados, permitiendo
 * una busqueda eficiente de fotones en el espacio 3D.
 * 
 * @param photons Vector de fotones que se utilizaran para construir el mapa.
 * @return PhotonMap Mapa de fotones construido a partir de los fotones dados.
 */
PhotonMap newPhotonMap(const std::vector<Photon>& photons){
    return PhotonMap(photons, PhotonAxisPosition());
}

/**
 * @brief Busca los fotones mas cercanos a una posicion dada en el mapa de fotones.
 * 
 * Esta funcion realiza una busqueda en el KDTree para encontrar los fotones
 * mas cercanos a la posicion de consulta especificada, utilizando una estimacion
 * del numero de fotones y un radio de busqueda.
 * 
 * @param map Mapa de fotones donde se realizara la busqueda.
 * @param query_position Punto que representa la posicion de consulta.
 * @param nphotons_estimate Estimacion del numero de fotones a buscar.
 * @param radius_estimate Estimacion del radio de busqueda.
 * @return std::vector<const Photon*> Vector de punteros a los fotones encontrados.
 */
std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate, float radius_estimate){
    return map.nearest_neighbors(
        query_position,
        nphotons_estimate,
        radius_estimate
    );
}

/**
 * @brief Busca los fotones mas cercanos a una posicion dada en el mapa de fotones.
 * 
 * Esta funcion realiza una busqueda en el KDTree para encontrar los fotones
 * mas cercanos a la posicion de consulta especificada, utilizando una estimacion
 * del numero de fotones.
 * 
 * @param map Mapa de fotones donde se realizara la busqueda.
 * @param query_position Punto que representa la posicion de consulta.
 * @param nphotons_estimate Estimacion del numero de fotones a buscar.
 * @return std::vector<const Photon*> Vector de punteros a los fotones encontrados.
 */
std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate){
    return map.nearest_neighbors(
        query_position,
        nphotons_estimate
    );
}

/**
 * @brief Sobrecarga del operador de salida para la clase Photon.
 * 
 * Esta funcion permite imprimir el objeto Photon en un formato legible.
 * 
 * @param os Flujo de salida donde escribir.
 * @param p Objeto Photon que se va a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Photon &p) {
    os << "Photon(Position: " << p.pos << ", Incident: " << p.incident << ", Flux: " << p.flux << ")";
    return os;
}