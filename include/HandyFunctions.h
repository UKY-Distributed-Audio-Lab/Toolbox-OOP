#ifndef HANDYFUNCTIONS_H
#define HANDYFUNCTIONS_H

#include <vector>
#include <algorithm>
#include "armadillo"
#include "sigpack.h"

using namespace arma;

long gcd(long a, long b);
mat  resize_and_zero_pad(std::vector<Col<double>> & newData);

template<typename T>
T find_max_vector_element(std::vector<T> in);

#endif