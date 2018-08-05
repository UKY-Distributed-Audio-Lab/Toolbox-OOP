#ifndef ATMATTEN_H
#define ATMATTEN_H

// A function to return the atmospheric attenuation of sound due to the vibrational relaxation times of oxygen and nitrogen.
// NOTE:  This function does not account for spherical spreading!
//
// Usage: [a] = atmAtten(T,P,RH,d,f)
//               a - attenuation of sound for input parameters in dB
//               T - temperature in deg C
//               P - static pressure in mmHg
//               RH - relative humidity in //
//               d - distance of sound propagation
//               f - frequency of sound (may be a vector)
//
// Nathan Burnside 10/5/04
// AerospaceComputing Inc.
// nburnside@mail.arc.nasa.gov
// Grant Cox 2018
// grantcox167@gmail.com
//
// References:   Bass, et al., "Journal of Acoustical Society of America", (97) pg 680, January 1995.
//               Bass, et al., "Journal of Acoustical Society of America", (99) pg 1259, February 1996.
//               Kinsler, et al., "Fundamentals of Acoustics", 4th ed., pg 214, John Wiley & Sons, 2000.

#include "armadillo"
#include <math.h>

double atmAtten(float temp, float pressure, float humidity, double distance, double freq);
arma::vec atmAtten(float temp, float pressure, float humidity, double distance, arma::vec freq);

#endif