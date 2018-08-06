#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    vec freqs = { 10, 100, 10e3, 10e4, 10e5, 10e6 };
    vec result = atmAtten(.2, 10, 20, 10, freqs);
    //printf("result: %f\n", result);
    result.print(); 
    return 0;
}