#include <string>
#include "ArrayToolbox.h"

int main(int argc, char* argv[]) {
    // std::vector<std::string> tests =
    //                         {"../man1.wav"};

    mat sig = randn(20,2);
    //mat sig = randn(20,1);
    uint32_t fs = 16000;
    std::vector<float> delay = { 0.1, 0.1 };
    //std::vector<float> delay = { 0.1 };

    sig.print();

    mat delayed = delayt(sig, fs, delay);

    for(int i = delayed.n_rows - 25; i < delayed.n_rows - 1; i++)
        printf("delayed sample: %d\t=\t%f\t%f\n\r", i, delayed(i,0), delayed(i,1));
    
    return 0;
}