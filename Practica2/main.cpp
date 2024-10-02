#include <iostream>
#include <memory>
#include <cmath>
#include "Vector.hpp"
#include "Point.hpp"
#include "Coordinate.hpp"
#include "Matrix.hpp"
#include "PPM.hpp"
using namespace std;

int main(){
    PPM i("../files/mpi_atrium_1.ppm");
    cout << i;
    i.save();
}