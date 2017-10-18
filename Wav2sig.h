#ifndef WAV2SIG_H
#define WAV2SIG_H

#include <string>
#include <vector>
#include "./libs/armadillo"

using namespace arma;

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
    uint64_t        numSamples;     // number of samples in the file
} wav_header;

class Wav2sig {
private:
     std::vector<wav_header> wavHeaders;  //container for the wav headers
     std::vector<std::string> fnames;    //filenames
     bool fs_flag;                 //flag to resample the file
     int fs;                       //resample file to this frequency
     bool tInt_flag;               //flag for time interval trimming (in seconds)
     std::vector<float> tInt;      //time interval (in seconds)
     bool weights_flag;            //flag to scale signals by weights provided
     std::vector<double> weights;  //n weights, as many as there are files, to
                                   //multiply by the normalized signal
     std::vector<vec> data;
     bool output_fdata;

public:
     Wav2sig();
     Wav2sig(std::vector<std::string> paths);
     Wav2sig(bool fs_flag, int fs,
          bool tInt_flag,std::vector<float> tInt,
          bool weights_flag, std::vector<double> weights,
          bool output_fdata, std::vector<std::string> fnames);

     int convert(std::string filepath, uint8_t column);
     int getFileSize(FILE * inFile);
     void outputFileData(wav_header & wavHeader, FILE * wavFile);
     int resample(unsigned int resample_fs);
};

#endif