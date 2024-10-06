#ifndef TONE_MAPPING_HPP
#define TONE_MAPPING_HPP

#include "PPM.hpp" 

void clamping(PPM& image);
void equalization(PPM& image);
void equalizationAndClamping(PPM& image, const double clampValue);
void gamma(PPM& image, double gammaValue);
void gammaAndClamping(PPM& image, double gammaValue);

#endif /* TONE_MAPPING_HPP */
