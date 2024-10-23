#include "Point.hpp"

std::ostream& operator<<(std::ostream& os, const Point &p){
    os << "Point(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}

Point::~Point(){
}

std::shared_ptr<Vector> operator-(Point const &p1, Point const &p2){
    return std::make_shared<Vector>(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
}

std::shared_ptr<Point> operator+(int32_t const s, Point const &p){
    return std::make_shared<Point>(s+p.x, s+p.y, s+p.z);
}

std::shared_ptr<Point> operator+(Point const &p, int32_t const s){
    return s+p;
}

double operator*(const Point& p, const Vector &v){
    return v*p;
}

double operator*(const Vector &v, const Point& p){
    return dotProduct(v, *(p - Point(0, 0, 0)));
}


