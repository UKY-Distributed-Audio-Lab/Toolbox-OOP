#ifndef DELAY_H
#define DELAY_H

#define FILTER_ORDER 4


#include "armadillo"
#include "sigpack.h"
#include <stdexcept>
#include <vector>
#include "HandyFunctions.h"

using namespace arma;

mat delayt(mat sigin, uint32_t fs, std::vector<float> delay_length);
vec delayt(vec sigin, uint32_t fs, float delay_length);

#endif