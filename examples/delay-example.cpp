#include <string>
#include "ArrayToolbox.h"

int main(int argc, char* argv[]) {
    std::vector<std::string> tests =
                            {"../man1.wav",
                             "../man2.wav"};

    
    /*
    This example used fibonnaci numbers to do a fun delay with the input
    the input is delayed twice then they are summed at the end.
    */
    wav2sig sig(tests);
    uint32_t fs = sig.get_channel_fs()[0];
    std::vector<float> delay_fib1 = { 0.610, 0.610 };
    std::vector<float> delay_fib2 = { 0.987, 0.987 };

    mat delayed1 = delayt(sig.filedata, fs, delay_fib1);
    mat delayed2 = delayt(sig.filedata, fs, delay_fib2);


    // for(uint16_t i = 1580; i < 1620; i++)
    //     printf("original:\t%f delayed:\t%f\n", sig.filedata(i,0), delayed(i,0));

    sig.filedata.resize(delayed1.n_rows, delayed1.n_cols);
    sig.filedata += delayed1;
    sig.filedata.resize(delayed2.n_rows, delayed2.n_cols);
    sig.filedata += delayed2;

    sig.write();
    return 0;
}