//
//File: wav2sig.cpp
//Purpose: opens wavfile, maipulates data for use in the Array Toolbox
//Author: Grant Cox, University of Kentucky Distributed Audio Lab, grant.cox@uky.edu

#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include "wav2sig.h"
#include "./libs/armadillo"

using namespace arma;

//default destructor
Wav2sig::Wav2sig() {
     fs_flag = false;
     fs = 0;
     tInt_flag = false;
     weights_flag = false;
     output_fdata = false;
}

Wav2sig::Wav2sig(std::vector<std::string> paths) {
     fs_flag = false;
     fs = 0;
     tInt_flag = false;
     weights_flag = false;
     output_fdata = false;
     fnames = paths;
     for (unsigned int i = 0; i < fnames.size(); i++)
          convert(fnames[i],i+1);
}

Wav2sig::Wav2sig(bool fs_flag, int fs,
     bool tInt_flag,std::vector<float> tInt,
     bool weights_flag, std::vector<double> weights,
     bool output_fdata, std::vector<std::string> fnames) {

}

/*******************************************************************************
Function: getFileSize
Purpose: get the size of the wave file opened in the program
@param: FILE pointer to the wave file
@return: integer, the size of the wavefile
*/
int Wav2sig::getFileSize(FILE * inFile) {
     fseek(inFile, 0, SEEK_END);
     unsigned int filesize = ftell(inFile);
     fseek(inFile, 0, SEEK_SET);
     return filesize;
}



/*******************************************************************************
Function: outputFileData
Purpose: prints data about the selected .wav file to the command line
@param: a wav_header struct by reference, a FILE pointer, integer number of samples
@return: void
*/
void Wav2sig::outputFileData(wav_header & wavHeader, FILE * wavFile) {
     std::cout << "\n\nComputing/Outputting Metadata\n";
     int filelength = getFileSize(wavFile);

     std::cout << "File is                    :" << filelength << " bytes." << std::endl;
     std::cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1]
          << wavHeader.RIFF[2] << wavHeader.RIFF[3] << std::endl;
     std::cout << "WAVE header                :" << wavHeader.WAVE[0]
          << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << std::endl;
     std::cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1]
          << wavHeader.fmt[2] << wavHeader.fmt[3] << std::endl;
     std::cout << "Data size                  :" << wavHeader.ChunkSize << std::endl;

     // Display the sampling Rate from the header
     std::cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << std::endl;
     std::cout << "Number of bits used        :" << wavHeader.bitsPerSample << std::endl;
     std::cout << "Number of channels         :" << wavHeader.NumOfChan << std::endl;
     std::cout << "Number of bytes per second :" << wavHeader.bytesPerSec << std::endl;
     std::cout << "Number of samples          :" << wavHeader.numSamples << std::endl;
     std::cout << "Data length                :" << wavHeader.Subchunk2Size << std::endl;
     std::cout << "Audio Format               :" << wavHeader.AudioFormat << std::endl;
     // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

     std::cout << "Block align                :" << wavHeader.blockAlign << std::endl;
     std::cout << "Data string                :" << wavHeader.Subchunk2ID[0]
          << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2]
          << wavHeader.Subchunk2ID[3] << std::endl;
}


int Wav2sig::convert(std::string filepath, uint8_t column) {
     wav_header wavHeader;
     int headerSize = sizeof(wav_header);
     //double * data = nullptr;

     //attempt to open the wavefile provided by the caller
     FILE * wavFile = fopen(filepath.c_str(),"r");
     if (wavFile == nullptr) {
          std::cerr << "ERROR: Unable to open file " << filepath << std::endl;
          return 1;
     }

     //read in the wave file by the header
     size_t bytesRead = fread(&wavHeader,1, headerSize,wavFile);

     //check for empty file
     if (bytesRead <= 0) {
          std::cerr << "ERROR: Empty wav file. Exiting..." << std::endl;
          return 1;
     }

     if (wavHeader.NumOfChan > 1) {
          std::cerr << "ERROR: wav2sig only accepts mono (1 channel) signals"
               << std::endl;
          return 1;
     }

     //read the data
     uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;  //Number of bytes per sample
     wavHeader.numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file
     static const uint16_t BUFFER_SIZE = 4096;
     int8_t * buffer = new int8_t[BUFFER_SIZE];


     vec sigvector; //make vector matrix to hold the data
     sigvector.resize(wavHeader.numSamples); //resize to size of data
     data.push_back(sigvector);    //put vector into column of data

     if (column > data.size() || column < 1) {     //errchecking
          std::cerr << "ERROR: column paramter must be in the range of columns"
                    << " of the data matrix." << std::endl;
          data.erase(data.end());
          return 1;
     }

     column--;
     int sampleCounter = 0;   //counter for array indexing (sampling)
     while ( (bytesRead = fread(buffer, sizeof buffer[0],
                         BUFFER_SIZE / (sizeof buffer[0]) , wavFile) ) > 0) {

          //increment over bytes read into the buffer
          //TODO For some reason, this algorithm loses the first 5-6 samples of
          //TODO the file.
          for(unsigned int i = 0; i < bytesRead; i+=2) { // bytesRead = 256 (frame size)
               int c = buffer[i+1] << 8 | buffer[i]; //combine 2 bytes into 16 bit sample size
               double d = c / 32768.0;               //convert to double floating point
               //data[sampleCounter] = d;              //store into array of data
               data[column](i) = d;                  //store into the appropriate column
               sampleCounter++;                      //increment counter
          }
     }


     delete[] buffer; buffer = nullptr; //remove buffer

     //outputFileData(wavHeader,wavFile);    //report data to command line

     fclose(wavFile);
     return 0;
}

int Wav2sig::resample(const unsigned int resample_fs) {


    return 0;
}