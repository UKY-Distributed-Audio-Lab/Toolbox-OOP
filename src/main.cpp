#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    vec freq = {-8*M_PI/9, -6*M_PI/9, -4*M_PI/9, -2*M_PI/9, 0, 2*M_PI/9, 4*M_PI/9, 6*M_PI/9, 8*M_PI/9}, 
        mag = {0, 0, 0, 1, 1, 1, 0, 0, 0}, 
        h;
    uint8_t order = 9;

    h = fir2(order, freq, mag);
    printf("\nh:\n");
    h.print();
}