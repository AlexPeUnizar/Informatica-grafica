#include "PhotonMap.hpp"

Photon::Photon(const Point &pos, const Vector& incident, const double& flux){
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

