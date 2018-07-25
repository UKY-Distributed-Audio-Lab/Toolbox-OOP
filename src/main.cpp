#include <string>
#include "ArrayToolbox.h"

int main(int argc, char* argv[]) {
    // std::vector<std::string> tests =
    //                         {"../man1.wav"};

    mat sig = randn(20);
    uint32_t fs = 16000;
    std::vector<float> delay = { 0.5 };

    for(uint8_t i = 0; i < sig.n_rows; i++)
        printf("Original sample: %d\t=\t%f\n\r",i,sig(i,0));

    mat delayed = delayt(sig, fs, delay);

    for(int i = 8000; i < 8020; i++)
        printf("delayed sample: %d\t=\t%f\n\r", i, delayed(i,0));

    return 0;
}