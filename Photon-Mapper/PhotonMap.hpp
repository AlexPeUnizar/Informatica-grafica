/**
 * @file PhotonMap.hpp
 * @author Alex
 * @brief Declaracion de la clase PhotonMap para el almacenamiento y busqueda de fotones utilizando un KDTree.
 * @date 2025-01-04
 * 
 */
#ifndef PHOTONMAP_HPP
#define PHOTONMAP_HPP

#include "kdtree.h"
#include "Vector.hpp"
#include "list"
#include "vector"
#include "Point.hpp"
#include "Color.hpp"

/**
 * @class Photon
 * @brief Clase que representa un foton en el mapa de fotones.
 * 
 * Esta clase almacena la posicion, la direccion incidente y el flujo del foton.
 */
class Photon{
private:
    Point pos;
    Vector incident;
    Color flux;

public:
    Photon() = delete;
    Photon(const Point &pos, const Vector& incident, const Color& flux);
    ~Photon() = default;
    double position(std::size_t i) const { return pos[i]; }
    Color getFlux() const { return flux; }
    Vector getIncident() const { return incident; }
    Point getPosition() const { return pos; }
    friend std::ostream& operator<<(std::ostream& os, const Photon &p);
};

/**
 * @struct PhotonAxisPosition
 * @brief Estructura para obtener la posicion de un foton en una dimension especifica.
 * 
 * Esta estructura define un operador que devuelve la coordenada del foton en la dimension dada.
 */
struct PhotonAxisPosition {
    double operator()(const Photon& p, std::size_t i) const {
        return p.position(i);
    }
};

using PhotonMap = nn::KDTree<Photon, 3, PhotonAxisPosition>;

PhotonMap newPhotonMap(const std::vector<Photon>& photons);
std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate, float radius_estimate);
std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate);



#endif /* PHOTONMAP_HPP */