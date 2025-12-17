#ifndef AABB_HPP
#define AABB_HPP

#include "Point.hpp"
#include "Ray.hpp"
#include <algorithm>
#include <limits>

struct AABB {
    Point mn;
    Point mx;

    AABB()
        : mn(Point( std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity())),
          mx(Point(-std::numeric_limits<double>::infinity(),
                   -std::numeric_limits<double>::infinity(),
                   -std::numeric_limits<double>::infinity())) {}

    AABB(const Point& a, const Point& b) : mn(a), mx(b) {}

    static AABB merge(const AABB& a, const AABB& b);

    bool hit(const Ray& r, double tMin, double tMax) const;
};

#endif
