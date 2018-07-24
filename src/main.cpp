#include <string>
#include "wav2sig.hpp"


int main(int argc, char* argv[]) {
    std::vector<std::string> tests =
                            {"../man1.wav",
                            "../man2.wav",
                            "../man3.wav"};

    
    int fs = 15000;
    std::vector<float> tInt = {1,3};
    std::vector<double> weights = { 1 , 1 , 1 };
    
    //**************Uncomment each to test****************//

    // wav2sig testsigs(tests);
    // testsigs.write();

    // wav2sig testsigs2(tests, fs);
    // testsigs2.write();

    // wav2sig testsigs3(tests, tInt);
    // testsigs3.write();

    // wav2sig testsigs4(tests, weights);
    // testsigs4.write();

    // wav2sig testsigs5(tests, fs, tInt);
    // testsigs5.write();

    // wav2sig testsigs6(tests, tInt, weights);
    // testsigs6.write();

    // wav2sig testsigs7(tests, fs, weights);
    // testsigs7.write();

    // wav2sig testsigs8(tests, fs, tInt, weights);
    // testsigs8.write();

    return 0;
}