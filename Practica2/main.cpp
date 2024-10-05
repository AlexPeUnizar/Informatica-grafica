#include <iostream>
#include <memory>
#include <cmath>
#include "Vector.hpp"
#include "Point.hpp"
#include "Coordinate.hpp"
#include "Matrix.hpp"
#include "PPM.hpp"
#include "ToneMapping.hpp"
using namespace std;

int main(){
    /*
    PPM i("../files/seymour_park.ppm");
    PPM i("../files/nancy_church_3.ppm");
    PPM i("../files/nancy_church_1.ppm");
    PPM i("../files/mpi_atrium_3.ppm");
    PPM i("../files/forest_path.ppm");
    PPM i("../files/mpi_atrium_1.ppm");
    PPM i("../files/nancy_church_2.ppm");
    */
    PPM i("../files/mpi_office.ppm");
    cout << i << endl;
    equalization(i);
    cout << i;
    i.save();
}