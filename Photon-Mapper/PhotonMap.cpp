#include "PhotonMap.hpp"

Photon::Photon(const Point &pos, const Vector& incident, const Color& flux){
    this->pos = pos;    
    this->incident = incident;    
    this->flux = flux;    
}

PhotonMap newPhotonMap(const std::list<Photon>& photons){
    return PhotonMap(photons, PhotonAxisPosition());
}

std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate, float radius_estimate){
    return map.nearest_neighbors(
        query_position,
        nphotons_estimate,
        radius_estimate
    );
}

std::ostream& operator<<(std::ostream& os, const Photon &p) {
    os << "Photon(Position: " << p.pos << ", Incident: " << p.incident << ", Flux: " << p.flux << ")";
    return os;
}