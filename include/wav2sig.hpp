#ifndef WAV2SIG_H
#define WAV2SIG_H

#include <string>
#include <vector>
#include "../libs/armadillo"

using namespace arma;

class wav2sig {
private:
     std::vector<std::string> fnames;   //filenames
     bool fs_flag;                      //flag to resample the file
     int fs;                            //resample file to this frequency
     //bool tInt_flag;                  //flag for time interval trimming (in seconds)
     std::vector<float> tInt;           //time interval (in seconds)
     //bool weights_flag;               //flag to scale signals by weights provided
     std::vector<double> weights;       //n weights, as many as there are files, to
                                        //multiply by the normalized signal
     
     
     //private functions
     vec trimFile(vec in); //TODO
     vec multiplyWeight(vec in, std::vector<float> & weights); //TODO

public:
     //public data
     std::vector<vec> filedata;    //hold in and out files


     //public members
     wav2sig();
     wav2sig(std::vector<std::string> paths);
     wav2sig(std::vector<std::string> paths, int in_fs);
     wav2sig(int in_fs,
          std::vector<float> in_tInt,
          std::vector<float> weights,
          std::vector<std::string> paths);

     void read(std::string filepath);
};

#endif