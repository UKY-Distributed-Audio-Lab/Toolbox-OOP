//File: wav2sig.cpp
//Purpose: opens wavfile, maipulates data for use in the Array Toolbox
//Author: Grant Cox, University of Kentucky Distributed Audio Lab, grant.cox@uky.edu

#include "../include/wav2sig.hpp"

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
    num_files = paths.size();

    for(int i = 0; i < paths.size(); i++) fnames.push_back(paths[i]);
    read();
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> paths, int in_fs) {
    fs_flag = true;
    fs = in_fs;
    num_files = paths.size();

    for(int i = 0; i < paths.size(); i++) fnames.push_back(paths[i]);
    read();
    resample_signals();
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(int in_fs,
    std::vector<float> in_tInt,
    std::vector<float> weights,
    std::vector<std::string> paths) {

    fs_flag = true;
    fs = in_fs;
    tInt = in_tInt;
    num_files = paths.size();

    //TODO test this
    for(int i = 0; i < paths.size(); i++) fnames.push_back(paths[i]);
    
    read();

    //filedata[i] = trimFile(filedata[i]);
    //filedata[i] = multiplyWeight(filedata[i],weights);
}

//////////////////////////////////////////////////////////////

void wav2sig::read() {
    uint8_t count = 0;
    int max_samples = 0;
    std::vector<AudioFile<double>> fdata(num_files); //hold raw samples
    //iterate through the filenames
    for (std::vector<std::string>::iterator i = fnames.begin(); i != fnames.end(); ++i) {
        fdata[count].load(*i);   //load the audio samples into the vector index

        cout << "Loaded " << *i << ", summary:\n\r";
        fdata[count].printSummary();

        samples_per_channel.push_back(fdata[count].getNumSamplesPerChannel());
        channel_fs.push_back(fdata[count].getSampleRate());
        ++count;
    }
    
    std::vector<int>::iterator it;
    it = std::max_element(samples_per_channel.begin(), samples_per_channel.end());
    max_samples = *it;

    filedata.zeros(max_samples, num_files); //size our darn matrix
    //lets get reading
    for(uint8_t fdata_it = 0; fdata_it < num_files; fdata_it++) {
        for(int samp_it = 0; samp_it < fdata[fdata_it].getNumSamplesPerChannel(); samp_it++) {
            filedata(samp_it,fdata_it) = fdata[fdata_it].samples[0][samp_it];
        }
    }
}

void wav2sig::resample_signals() {
    std::vector<Col<double>> resampled_sigs(num_files);
    
    for(uint8_t i = 0; i < num_files; i++) {
        //convert the fs ratio into a p / q rational used in resampling
        double fs_ratio = fs / channel_fs[i];
        double integral = std::floor(fs_ratio);
        double frac = fs_ratio - integral;
        const long precision = 1000000000; // This is the accuracy.

        long gcd_ = gcd(round(frac * precision), precision);

        long denominator = precision / gcd_;
        long numerator = round(frac * precision) / gcd_;
        numerator += integral * denominator;
        
        // having the numerator and denominator, the upsample and downsample functions can
        // be called
        Col<double> to_process = filedata.col(i); //upsample then downsample
        to_process = sp::upsample(to_process,numerator);
        to_process = sp::downsample(to_process,denominator);
        resampled_sigs[i] = to_process;   //put into resampled vector
        channel_fs[i] = fs;               //note new fs for each file
        samples_per_channel[i] = to_process.size(); //update samps per channel
    }

    //now need to recreate filedata matrix to match resampled sigs
    for(int i = 0; i < num_files; i++)  
        samples_per_channel[i] = resampled_sigs[i].size();
    std::vector<int>::iterator it;  //find new maximum size
    it = std::max_element(samples_per_channel.begin(), samples_per_channel.end());
    int max_samples = *it;
    
    //reset filedata
    filedata.zeros(max_samples, num_files);
    
    //put the data back
    for(int i = 0; i < num_files; i++)  filedata.col(i) = resampled_sigs[i];
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

    return trimmed;
} //TODO test


//////////////////////////////////////////////////////////////


vec wav2sig::multiplyWeight(vec in, std::vector<float> & weights) {
    vec dum; return dum; //TODO
}//TODO

//greatest common denominator
long wav2sig::gcd(long a, long b) {
    if (a == 0)
        return b;
    else if (b == 0)
        return a;

    if (a < b)
        return gcd(a, b % a);
    else
        return gcd(b, a % b);
}