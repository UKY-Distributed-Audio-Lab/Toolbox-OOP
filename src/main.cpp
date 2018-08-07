#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    vec delays = { 1, 1, 1 }, scls = {.4, .3, .2};
    int fs = 44100;
    double speedofsound = 350;
    impres myimpres = roomimpres(delays, scls, speedofsound, fs);
}