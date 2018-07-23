#include <iostream>
#include <string>
#include "wav2sig.hpp"


int main(int argc, char* argv[]) {
    std::vector<std::string> tests =
                            {"../man1.wav",
                            "../man2.wav",
                            "../man3.wav"};

    
    int fs = 15000;
    std::vector<float> tInt = {1.5,2};
    std::vector<float> weights = { 1 , 1 , 1 };
    
    //-----------------------------Test only supplying filenames-------------------------
    wav2sig testsigs(tests);
    printf("\n\n\r");

    //---------------------------Test supplying fnames and fs----------------------------
    wav2sig testsigs2(tests, fs);
    testsigs2.write();
    printf("\n\n\r");

    //---------------------------Test supplying fnames, fs, tInt--------------------------
    wav2sig testsigs3(tests, fs, tInt);

    printf("\n\n\r");
    return 0;
}