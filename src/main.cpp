#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    // vec freqs = { 450, 10e3, 20e3 };
    //vec result = atmAtten(22, 480, 50, 20, freqs);
    double result = atmAtten(22, 480, 50, 20, 20e3);
    printf("result: %f\n", result);
    return 0;
}