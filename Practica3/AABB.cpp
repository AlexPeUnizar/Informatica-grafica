#include "AABB.hpp"


AABB AABB::merge(const AABB& a, const AABB& b) {
    return AABB(
        Point(std::min(a.mn.x, b.mn.x), std::min(a.mn.y, b.mn.y), std::min(a.mn.z, b.mn.z)),
        Point(std::max(a.mx.x, b.mx.x), std::max(a.mx.y, b.mx.y), std::max(a.mx.z, b.mx.z))
    );
}

bool AABB::hit(const Ray& r, double tMin, double tMax) const {
    // Slab method
    for (int axis = 0; axis < 3; ++axis) {
        double origin = (axis == 0) ? r.origin.x : (axis == 1) ? r.origin.y : r.origin.z;
        double dir    = (axis == 0) ? r.dir.x    : (axis == 1) ? r.dir.y    : r.dir.z;
        double minv   = (axis == 0) ? mn.x       : (axis == 1) ? mn.y       : mn.z;
        double maxv   = (axis == 0) ? mx.x       : (axis == 1) ? mx.y       : mx.z;

        double invD = 1.0 / dir;
        double t0 = (minv - origin) * invD;
        double t1 = (maxv - origin) * invD;
        if (invD < 0.0) std::swap(t0, t1);

        tMin = std::max(tMin, t0);
        tMax = std::min(tMax, t1);
        if (tMax <= tMin) return false;
    }
    return true;
}