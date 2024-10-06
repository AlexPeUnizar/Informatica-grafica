#include <iostream>
#include <memory>
#include <cmath>
#include <string>
#include "Vector.hpp"
#include "Point.hpp"
#include "Coordinate.hpp"
#include "Matrix.hpp"
#include "PPM.hpp"
#include "ToneMapping.hpp"
using namespace std;

const vector<string> files = vector<string>({
    /*
    */
    "../files/seymour_park.ppm",
    "../files/nancy_church_3.ppm",
    "../files/nancy_church_1.ppm",
    "../files/mpi_atrium_3.ppm",
    "../files/forest_path.ppm",
    "../files/mpi_atrium_1.ppm",
    "../files/nancy_church_2.ppm",
    "../files/mpi_office.ppm"
});

int main(){

    for (size_t i = 0; i < files.size(); i++)
    {
        PPM image(files[i]);
        cout << image << endl;
        //equalization(image);
        equalizationAndClamping(image, 100);
        //clamping(image);
        gamma(image,2);
        cout << image << endl;
        image.save("out_" + to_string(i) + ".ppm");
    }
}