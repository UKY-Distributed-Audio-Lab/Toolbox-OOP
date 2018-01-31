#ifndef WAV2SIG_H
#define WAV2SIG_H

#include <string>
#include <vector>
#include "./AudioFile.h"
#include "../libs/armadillo"

using namespace arma;

class wav2sig {
private:
     std::vector<std::string> fnames;    //filenames
     bool fs_flag;                 //flag to resample the file
     int fs;                       //resample file to this frequency
     //bool tInt_flag;               //flag for time interval trimming (in seconds)
     std::vector<float> tInt;      //time interval (in seconds)
     //bool weights_flag;            //flag to scale signals by weights provided
     std::vector<double> weights;  //n weights, as many as there are files, to
                                   //multiply by the normalized signal
     
     vec trimFile(vec in, std::vector<float> & tInt); //TODO
     vec multiplyWeight(vec in, std::vector<float> & weights); //TODO

public:
     std::vector<vec> filedata;    //hold in and out files
     
     wav2sig();
     wav2sig(std::vector<std::string> paths);
     wav2sig(std::vector<std::string> paths, int in_fs);
     wav2sig(int in_fs,
          std::vector<float> tInt,
          std::vector<float> weights,
          std::vector<std::string> paths);

     void read(std::string filepath);
};

#endif