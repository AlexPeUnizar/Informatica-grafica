#ifndef TONE_MAPPING_HPP
#define TONE_MAPPING_HPP

#include "PPM.hpp" 

void clamping(PPM& image);
void equalization(PPM& image);
void equalizationAndClamping(PPM& image);
void gamma(PPM& image);
void gammaAndClamping(PPM& image);



#endif /* TONE_MAPPING_HPP */
