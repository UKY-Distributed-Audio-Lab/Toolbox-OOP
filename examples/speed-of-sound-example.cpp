#include <string>
#include "ArrayToolbox.h"

/*
Demo program for speed of sound
passing:
temp = 22; % in centigrade
press = 29.92; % in inches of Hg
hum = 38; % percent humidity

should yield 345.098762 m/s
*/

int main(int argc, char* argv[]) {
    double temp = stof(argv[1]);
    double humidity = stof(argv[2]);
    double pressure = stof(argv[3]);

    double sos = SpeedOfSound(temp, humidity, pressure);
    printf("temp:\t%f\nhumidity:\t%f\npressure:\t\n", temp, humidity, pressure);
    printf("Speed of sound is: %f\n\r", sos);
    return 0;
}