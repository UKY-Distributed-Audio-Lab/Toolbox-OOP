#ifndef HANDYFUNCTIONS_H
#define HANDYFUNCTIONS_H

#include <vector>
#include <algorithm>
#include "armadillo"
#include "sigpack.h"

using namespace arma;

long gcd(long a, long b);
mat  resize_and_zero_pad(std::vector<Col<double>> & newData);
vec  fill_vec_between_limits(int l1, int l2);

template<typename T>
T find_max_vector_element(std::vector<T> in);

#endif