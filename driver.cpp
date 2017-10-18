#include <iostream>
#include <string>
#include "Wav2sig.h"

int main(int argc, char* argv[]) {
     std::vector<std::string> tests =
                              {"/media/x/WINDOWSHDD3/Git/Array-Toolbox/man1.wav",
                              "/media/x/WINDOWSHDD3/Git/Array-Toolbox/man2.wav",
                              "/media/x/WINDOWSHDD3/Git/Array-Toolbox/man3.wav"};

     Wav2sig testsigs(tests);

     std::cout << "got the signals" << std::endl;

     testsigs.resample(1,25000);

     return 0;
}