//
//File: wav2sig.cpp
//Purpose: opens wavfile, maipulates data for use in the Array Toolbox
//Author: Grant Cox, University of Kentucky Distributed Audio Lab, grant.cox@uky.edu
//        (process adapted from
//        https://stackoverflow.com/questions/13660777/c-reading-the-data-part-of-a-wav-file)
//

#include <fstream>
#include <iostream>
#include <string>
#include <cstdint>
#include "wav2sig.h"
#include <Eigen/Dense>

using Eigen::VectorXf;

/*******************************************************************************
struct: WAV_HEADER
data: allocation for each byte of data in a general .wav file.
*/
typedef struct WAV_HEADER {
     /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,
                                    //257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} wav_header;


//default destructor
Wav2sig::Wav2sig() {
     fs_flag = false;
     fs = 0;
     tInt_flag = false;
     weights_flag = false;
}

Wav2sig::Wav2sig(std::vector<std::string> paths) {
     fs_flag = false;
     fs = 0;
     tInt_flag = false;
     weights_flag = false;
     fnames = paths;
     for (unsigned int i = 0; i < fnames.size(); i++)
          convert(fnames[i],i+1);
}

Wav2sig::Wav2sig(bool fs_flag, int fs,
     bool tInt_flag,std::vector<float> tInt,
     bool weights_flag, std::vector<double> weights,
     std::vector<std::string> fnames) {

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
// void wav2sig::outputFileData(wav_header & wavHeader, FILE * wavFile, int numSamples) {
//      std::cout << "\n\nComputing/Outputting Metadata\n";
//      int filelength = getFileSize(wavFile);
//
//      std::cout << "File is                    :" << filelength << " bytes." << std::endl;
//      std::cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1]
//           << wavHeader.RIFF[2] << wavHeader.RIFF[3] << std::endl;
//      std::cout << "WAVE header                :" << wavHeader.WAVE[0]
//           << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << std::endl;
//      std::cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1]
//           << wavHeader.fmt[2] << wavHeader.fmt[3] << std::endl;
//      std::cout << "Data size                  :" << wavHeader.ChunkSize << std::endl;
//
//      // Display the sampling Rate from the header
//      std::cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << std::endl;
//      std::cout << "Number of bits used        :" << wavHeader.bitsPerSample << std::endl;
//      std::cout << "Number of channels         :" << wavHeader.NumOfChan << std::endl;
//      std::cout << "Number of bytes per second :" << wavHeader.bytesPerSec << std::endl;
//      std::cout << "Number of samples          :" << numSamples << std::endl;
//      std::cout << "Data length                :" << wavHeader.Subchunk2Size << std::endl;
//      std::cout << "Audio Format               :" << wavHeader.AudioFormat << std::endl;
//      // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
//
//      std::cout << "Block align                :" << wavHeader.blockAlign << std::endl;
//      std::cout << "Data string                :" << wavHeader.Subchunk2ID[0]
//           << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2]
//           << wavHeader.Subchunk2ID[3] << std::endl;
// }




/*
Example Call:
std::string paths[3] = {"/media/x/WINDOWSHDD3/Git/Array-Toolbox/man1.wav",
                         "/media/x/WINDOWSHDD3/Git/Array-Toolbox/man2.wav",
                         "/media/x/WINDOWSHDD3/Git/Array-Toolbox/man3.wav"};

double **data = new double*[3]; //allocate 2d array for data
int num_samples[3];             //keep track of number of samples for each

//get data from wav2sig
for(int i = 0; i < 3; i++)  data[i] = wav2sig(paths[i], num_samples[i]);
*/
int Wav2sig::convert(std::string filepath, int column) {
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
     uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file
     static const uint16_t BUFFER_SIZE = 4096;
     int8_t * buffer = new int8_t[BUFFER_SIZE];


     VectorXf sigvector; //make vector matrix to hold the data
     sigvector.resize(numSamples); //resize to size of data
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

     //outputFileData(wavHeader,wavFile, numSamples);    //report data to command line

     fclose(wavFile);
     return 0;
}

void Wav2sig::printsigs() {
     for(unsigned int i = 0; i < data.size(); i++) {
          std::cout << "\n\nSamples 0 - 49 for " << fnames[i] << "\n\n";
          for(unsigned int j = 0; j < 50; j++)
               std::cout << data[i](j) << " ";
     }
}