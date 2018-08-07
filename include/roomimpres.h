#ifndef ROOMIMPRES_H
#define ROOMIMPRES_H

#include "armadillo"
#include "sigpack.h"
#include "atmAtten.h"
#include <math.h>

using namespace arma;

//room impulse response

//  This function computes the impulse response of a source-microphone pair in a room
//  modeled by a direct path and a sequence of image/multipath scatterers described by
//  delay times in vector DLAYS and corresponding attenuation factors in vector SCLS.
//  In addition, the generated impulse response accounts for the frequency
//  dependent attenuation in the air, based on vectors in data structure
//  SFAC.
//
//     [impres, t] = roomimpres(dlays, scls, c, fs, sfac)
//
//  The following parameters must be supplied at the input:
//  DLAYS  => Vector with sequence of delays in seconds representing multipath
//            interference
//  SCLS   => Vector with scale factors (reflection coefficients) correspoding to signals
//                    delayed by each element in DLAYS
//  C      => the speed of sound in meters per second
//  FS     => the sampling frequency for the impulse response
//  SFAC   => (optional) data structure with the frequency dependent attenuation
//                     vectors:
//                     sfac.freq = vector of frequencies where attenuation values are provided
//                     sfac.atten = vector of corresponding attenuation values in dB per meter (must be positive)
//                      see function atmAtten() for generating these points
//                      based on environmental conditions.
//                      The default value is set according the the ISO 9613-1 for temperature = 22 C, pressure
//                      29.92 inHg, Relative Humidity 38%.
//                      
// The outputs are:
// IMPRES => Vector containing the impulse response
// T      => optional parameter, a vector of time axis points corresponding
//           to the impuse response IMPRES
//
//     written by Kevin D. Donohue (donohue@engr.uky.edu) September 2005
//     (updated June 2009)
//
//     written for c++ by Grant Cox; grantcox167@gmail.com, grant.cox@uky.edu
//     August 2018

struct impres {
    vec response;
    vec time_axis;
};

struct sfac {
    vec freq;
    vec atten;
};

impres roomimpres(vec &dlays, vec &scls, double &c, int &fs);
impres roomimpres(vec &dlays, vec &scls, double &c, int &fs, sfac sfac_in);

#endif