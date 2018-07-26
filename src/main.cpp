#include <string>
#include "ArrayToolbox.h"

int main(int argc, char* argv[]) {
    // std::vector<std::string> tests =
    //                         {"../man1.wav"};

    mat sig = randn(20);
    uint32_t fs = 16000;
    std::vector<float> delay = { 0.5 };

    sig.print();

    mat delayed = delayt(sig, fs, delay);

    for(int i = delayed.n_rows - 25; i < delayed.n_rows - 1; i++)
        printf("delayed sample: %d\t=\t%f\n\r", i, delayed(i,0));

    return 0;
}