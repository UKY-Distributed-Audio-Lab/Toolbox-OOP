#include <iostream>
#include <string>
#include "../include/wav2sig.hpp"


int main(int argc, char* argv[]) {
     std::vector<std::string> tests =
                              {"../man1.wav",
                              "../man2.wav",
                              "../man3.wav"};

     wav2sig testsigs(tests);
     for(int i = 0; i < 3; i++) {
          std::cout << i << std::endl;
          for (int j = 0; j < 10; j++)
               std::cout << testsigs.filedata[i][j] << "\t";
          std::cout << std::endl;
     }

     std::cout << "got the signals" << std::endl;
     std::cout << "testing1" << std::endl;
     return 0;
}