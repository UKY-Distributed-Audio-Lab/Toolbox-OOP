#ifndef WAV2SIG_H
#define WAV2SIG_H

/*
Algorithm:
1) take the file inputs, load them into a vector of AudioFiles
2) make a master matrix based on the largest audiofile input to the function
*/

#define unix

#include <string.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "../libs/armadillo"
#include "../include/AudioFile.h"
#include "../libs/sigpack/sigpack.h"

using namespace arma;

class wav2sig {
private:
    std::vector<std::string> fnames;   //filenames
    uint8_t num_files;
    bool fs_flag;                      //flag to resample the file
    float fs;                            //resample file to this frequency
    //bool tInt_flag;                  //flag for time interval trimming (in seconds)
    std::vector<float> tInt;           //time interval (in seconds)
    //bool weights_flag;               //flag to scale signals by weights provided
    std::vector<double> weights;       //n weights, as many as there are files, to
                                    //multiply by the normalized signal
    std::vector<int>    samples_per_channel;
    std::vector<int>    channel_fs;          //fs for each channel
    
    
    //private functions
    void resample_signals();
    vec trimFile(vec in); //TODO
    vec multiplyWeight(vec in, std::vector<float> & weights); //TODO
    long gcd(long a, long b);

public:
    //public data
    mat filedata;    //hold in and out files


    //public members
    wav2sig();
    wav2sig(std::vector<std::string> paths);
    wav2sig(std::vector<std::string> paths, int in_fs);
    wav2sig(int in_fs,
        std::vector<float> in_tInt,
        std::vector<float> weights,
        std::vector<std::string> paths);

    void read();
};

#endif