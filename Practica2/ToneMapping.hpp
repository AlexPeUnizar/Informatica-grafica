#ifndef TONE_MAPPING_HPP
#define TONE_MAPPING_HPP

#include "PPM.hpp" 

void clamping(PPM& image, double clampValue = 1.0);
void equalization(PPM& image);
void equalizationAndClamping(PPM& image, const double clampValue);
void gamma(PPM& image, double gammaValue);
void gammaAndClamping(PPM& image, double gammaValue, double clampValue = 1.0);

#endif /* TONE_MAPPING_HPP */
