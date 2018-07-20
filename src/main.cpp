#include <iostream>
#include <string>
#include "../include/wav2sig.hpp"


int main(int argc, char* argv[]) {
    std::vector<std::string> tests =
                            {"../man1.wav",
                            "../man2.wav",
                            "../man3.wav"};

    
    int fs = 18000;
    std::vector<float> tInt = {1.5,2};
    std::vector<float> weights = { 1 , 1 , 1 };
    
    //-----------------------------Test only supplying filenames-------------------------
    wav2sig testsigs(tests);
    for(int i = 0; i < 10; i++) 
        printf("data from sample 0 to 10 matrix 1 %f\t%f\t%f\n\r",
            testsigs.filedata(i,0),testsigs.filedata(i,1),testsigs.filedata(i,2));
    
    printf("rows in matrix 1: %d\n\r", testsigs.filedata.col(0).n_rows);

    printf("\n\n\r");

    //---------------------------Test supplying fnames and fs----------------------------
    wav2sig testsigs2(tests, fs);
    for(int i = 0; i < 10; i++)
        printf("data from sample 0 to 10 matrix 2 %f\t%f\t%f\n\r", 
            testsigs2.filedata(i,0),testsigs2.filedata(i,1),testsigs2.filedata(i,2));
    
    printf("rows in matrix 2: %d\n\r", testsigs2.filedata.col(0).n_rows);

    printf("\n\n\r");

    //---------------------------Test supplying fnames, fs, tInt--------------------------
    wav2sig testsigs3(tests, fs, tInt);
    for(int i = 1; i < 10; i++)
        printf("data from sample 0 to 10 matrix 3 %f\t%f\t%f\n\r", 
            testsigs3.filedata(i,0),testsigs3.filedata(i,1),testsigs3.filedata(i,2));
    
    printf("rows in matrix 2: %d\n\r", testsigs3.filedata.col(0).n_rows);

    printf("\n\n\r");
    return 0;
}