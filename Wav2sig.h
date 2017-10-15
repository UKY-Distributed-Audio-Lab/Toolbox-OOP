#ifndef WAV2SIG_H
#define WAV2SIG_H

#include <string>
#include <vector>
#include <Eigen/Dense>
using Eigen::VectorXf;


class Wav2sig {
private:
     std::vector<std::string> fnames;    //filenames
     bool fs_flag;                 //flag to resample the file
     int fs;                       //resample file to this frequency
     bool tInt_flag;               //flag for time interval trimming (in seconds)
     std::vector<float> tInt;      //time interval (in seconds)
     bool weights_flag;            //flag to scale signals by weights provided
     std::vector<double> weights;  //n weights, as many as there are files, to
                                   //multiply by the normalized signal
     std::vector<VectorXf> data;          //n x n matrix of signal samples

public:
     Wav2sig();
     Wav2sig(std::vector<std::string> paths);
     Wav2sig(bool fs_flag, int fs,
          bool tInt_flag,std::vector<float> tInt,
          bool weights_flag, std::vector<double> weights,
          std::vector<std::string> fnames);

     int getFileSize(FILE * inFile);
     //void outputFileData(wav_header & wavHeader, FILE * wavFile, int numSamples);
     int convert(std::string filepath, int column);
     void printsigs();
};

#endif