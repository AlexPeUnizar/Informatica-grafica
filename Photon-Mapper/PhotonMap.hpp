#ifndef PHOTONMAP_HPP
#define PHOTONMAP_HPP

#include "kdtree.h"
#include "Vector.hpp"
#include "list"
#include "vector"
#include "Point.hpp"
#include "Color.hpp"

const size_t MAX_PHOTONS = 100000;

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

struct PhotonAxisPosition {
    double operator()(const Photon& p, std::size_t i) const {
        return p.position(i);
    }
};

using PhotonMap = nn::KDTree<Photon, 3, PhotonAxisPosition>;

PhotonMap newPhotonMap(const std::list<Photon>& photons);
std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate, float radius_estimate);
std::vector<const Photon*> search_nearest(const PhotonMap& map, const Point& query_position, unsigned long nphotons_estimate);



#endif /* PHOTONMAP_HPP */