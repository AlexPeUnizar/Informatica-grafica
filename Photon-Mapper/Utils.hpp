#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <cstdint>
#include "Point.hpp"
#include "Vector.hpp"

/* SETTINGS */

const size_t MAX_BOUNCES = 6;
const size_t MAX_PATHS = 1;

const size_t MAX_RAYS_PER_PIXEL = 64;
const size_t IMAGE_WIDTH = 512;
const size_t IMAGE_HEIGHT = 512;

const size_t MAX_PHOTONS = 100000;
const size_t MAX_NEIGHBORS = 100; // Nearest neighbors for photon search

/* FUNCTIONS */
double randomDouble(double min, double max);
double randomDouble();
Vector randomDirection();
Vector randomDirection(const Point& point, const Vector& normal);
#endif /* UTILS_HPP */