#ifndef REGMICS_H
#define REGMICS_H

//  This function generates the microphone coordinates for a regular
//  plane array placement over a plane or cube.
//
//      mpos = regmicsplane(fom, sp, geom)
// 
//  The inputs are:
//  FOM => the field over which the mics are placed. FOM is a 3 by 3
//         matrix where the first and last column define the opposite corners
//         of a rectangular space within which the mics are distributed. The
//         2nd column is an additional point that defines the plane.
//  SP =>  the spacing between mics in meters.  If a scalar, then spacing
//         is the same in all dimensions, otherwise if a 3 element vector
//         it defines the spacing in the x,y, and z directions (x,y,z).
//  GEOM => (optional input) flag indicating that the geometry of the spacing
//           is either rectangular or hexagonal.The options are:
//                GEOM = 'Rect' (default) is a rectilinear arrangment
//                GEOM = 'Hex' is a hexagonal spacing (in this case SP must be a scalar).


//  The first mic is placed at the first point (first column) in FOM. The
//  subsequent mics are placed with a constant spacing along the plane defined
//  by the FOM.  The last mic will be placed at the furthest point from the
//  beginning but still within or on the boundaries defined by FOM. 
//  The output will be columnwise coordinates of the microphones in matrix
//  MPOS.  The dimensionality of the output coordinates in MPOS will be the
//  same as those in FOM.
//    Written by Kevin D. Donohue (donohue@engr.uky.edu) July 2005, updated
//    June 2008.

//  Written for C++ by Grant Cox (grantcox167@gmail.com, grant.cox@uky.edu) August 2018

#include <stdexcept>
#include "armadillo"
#include <math.h>

using namespace arma;


//for these, if geom == true -> rectilinear, if geom == false -> hexagonal
mat regmicsplane(mat fom, double sp, bool geom);
mat regmicsplane(mat fom, vec sp, bool geom);

#endif