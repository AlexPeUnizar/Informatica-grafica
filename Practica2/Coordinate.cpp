#include "Coordinate.hpp"

Coordinate::Coordinate(double x, double y, double z, double w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Coordinate::~Coordinate(){
}

Coordinate::Coordinate(){
}

std::ostream& operator<<(std::ostream& os, const Coordinate &c){
    os << "Coordinate(" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ")";
    return os;
}

std::shared_ptr<Matrix> baseChange(const Coordinate& origin, const Coordinate& u, const Coordinate& v, const Coordinate& w){
    std::shared_ptr<Matrix> m = identity();
    (*m)[0][3] = origin.x;
    (*m)[1][3] = origin.y;
    (*m)[2][3] = origin.z;
    
    (*m)[0][0] = u.x;
    (*m)[1][0] = u.y;
    (*m)[2][0] = u.z;

    (*m)[0][1] = v.x;
    (*m)[1][1] = v.y;
    (*m)[2][1] = v.z;

    (*m)[0][2] = w.x;
    (*m)[1][2] = w.y;
    (*m)[2][2] = w.z;
    return m;
}

std::shared_ptr<Coordinate> operator*(const Matrix& m, const Coordinate& c){
    double new_x, new_y, new_z, new_w;

    new_x = m[0][0] * c.x + m[0][1] * c.y + m[0][2] * c.z + m[0][3] * c.w;
    new_y = m[1][0] * c.x + m[1][1] * c.y + m[1][2] * c.z + m[1][3] * c.w;
    new_z = m[2][0] * c.x + m[2][1] * c.y + m[2][2] * c.z + m[2][3] * c.w;
    new_w = m[3][0] * c.x + m[3][1] * c.y + m[3][2] * c.z + m[3][3] * c.w;
   
    /* normalizar
    if(c.w == 1){
        new_x = new_x / new_w; 
        new_y = new_y / new_w; 
        new_z = new_z / new_w;
        new_w = new_w / new_w; 
    }else{
        new_w = 0;
    }
    */

    return std::make_shared<Coordinate>(new_x, new_y, new_z, new_w);
}