#include "speedofsound.h"

inline double vp(double temp){
    return pow(10, ( (-7.90298)*(373.16/(temp+273.16)-1)) + (5.02808*log10(373.16/(temp+273.16))) - (1.3816*pow(10,-7)*(pow(10,(11.334*(1-(temp+273.16)/373.16))-1)) + (8.1328*pow(10,-3)*(pow(10,-3.49149*(373.16/(temp+273.16) - 1)) - 1)) ) )*(29.9213);
};

inline double SpeedOfSound(double temp, double RH, double p) {
    return 91.30029124144035 * sqrt(273+temp) * sqrt((p*(7.*p+0.01*RH * vp(temp))) / ((29.*p-0.11*RH * vp(temp)) * (5.*p+0.01*RH * vp(temp))));
};