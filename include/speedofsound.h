#ifndef SPEEDOFSOUND_H
#define SPEEDOFSOUND_H

#include "math.h"

#define SPEED_OF_SOUND_GENERAL 343.0

/*
From Matlab Toolbox:
% This function computes the speed of sound given room temperature,
% humidity, and air pressure
%
%   [cw] = SpeedOfSound(temp,RH,p)
%
% with inputs, TEMP the temperature in Centigrade, RH the relative humidity in percent
% and P the air pressure in mmHg.
% Forumla used:
% cw=(331.45*sqrt(1+(temp/273)))*(4.5513*sqrt(((7+((0.01*RH*vp)/p))/(5+((0.01*RH*vp)/p)))/(29-11*((0.01*RH*vp)/p)))
% simplified is:
% cw=91.30029124144035*sqrt(273+temp)*sqrt((p*(7.*p+0.01*RH*vp))/((29.*p-0.11*RH*vp)*(5.*p+0.01*RH*vp)))
% where p is the ambient pressure, t is the ambient temperature, RH is the relative humidity, and vp is
% the vapor pressure of water as a function of t. 
*/
inline double vp(double temp);

inline double SpeedOfSound(double temp, double RH, double p);

#endif