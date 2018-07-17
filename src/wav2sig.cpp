//File: wav2sig.cpp
//Purpose: opens wavfile, maipulates data for use in the Array Toolbox
//Author: Grant Cox, University of Kentucky Distributed Audio Lab, grant.cox@uky.edu

#include <iostream>
#include <string>
#include "../include/wav2sig.hpp"
#include "../include/AudioFile.h"

//////////////////////////////////////////////////////////////
//default destructor
wav2sig::wav2sig() {
     fs_flag = false;
     fs = 0;
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> paths) {
     fs_flag = false;
     fs = 0;

     for(int i = 0; i < paths.size(); i++) {
          fnames.push_back(paths[i]);
          read(paths[i]);
     }
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> paths, int in_fs) {
     fs_flag = true;
     fs = in_fs;

     for(int i = 0; i < paths.size(); i++) {
          fnames.push_back(paths[i]);
          read(paths[i]);
     }
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(int in_fs,
     std::vector<float> in_tInt,
     std::vector<float> weights,
     std::vector<std::string> paths) {

     fs_flag = true;
     fs = in_fs;
     tInt = in_tInt;

     //TODO test this
     for(int i = 0; i < paths.size(); i++) {
          fnames.push_back(paths[i]);
          read(paths[i]);

          filedata[i] = trimFile(filedata[i]);
          printf("\nback to wav2sig()\n");
          //filedata[i] = multiplyWeight(filedata[i],weights);
     }
}

//////////////////////////////////////////////////////////////


void wav2sig::read(std::string filepath) {
     AudioFile<double> in;    //read raw data in to audiofile object
     in.load(filepath);

     if(fs_flag) {            //if resample flag
          in.setSampleRate(fs);
          std::cout << "Resampled " << filepath << " to " << fs << std::endl;
     }
     std::cout << "Loaded " << filepath << ", summary:" << std::endl;
     in.printSummary();

     vec temp(in.getNumSamplesPerChannel());      //put into armadillo vec
     for(int i = 0; i < in.getNumSamplesPerChannel(); i++) {
          temp[i] = in.samples[0][i];
     }
     filedata.push_back(temp);                    //add to the data
}

//////////////////////////////////////////////////////////////
//

vec wav2sig::trimFile(vec in) {
     float time_index_1 = (float)fs * tInt[0];
     float time_index_2 = (float)fs * tInt[1];
     float num_samps = time_index_2 - time_index_1;

     int i1 = (int)time_index_1, i2 = (int)time_index_2;

     vec trimmed = zeros((int)num_samps);

     int trim_index = 0;
     for(int j = i1; j < i2; j++) {          //TODO TEST THIS
          trimmed[trim_index] = in[j];
          trim_index++;
     }

     printf("\nfinished trimming.\n");
     return trimmed;
} //TODO test


//////////////////////////////////////////////////////////////


vec wav2sig::multiplyWeight(vec in, std::vector<float> & weights) {
     vec dum; return dum; //TODO
}//TODO
