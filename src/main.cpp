#include <iostream>
#include <string>
#include "../include/wav2sig.hpp"
#include "../include/AudioFile.h"


int main(int argc, char* argv[]) {
     std::vector<std::string> tests =
                              {"../man1.wav",
                              "../man2.wav",
                              "../man3.wav"};

     
     int fs = 16000;
     std::vector<float> tInt = {1.5,2};
     std::vector<float> weights = { 1 , 1 , 1 };
     
     wav2sig testsigs(fs, tInt, weights, tests);

     // for(int i = 0; i < 3; i++) {
     //      AudioFile<double> out;
     // 
     // }
     return 0;
}