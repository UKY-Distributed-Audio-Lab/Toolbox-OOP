#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    vec freqs = { 450, 10e3, 20e3 };
    vec result = atmAtten(.9, 20, 20, 20, freqs);
    //printf("result: %f\n", result);
    result.print(); 
    return 0;
}