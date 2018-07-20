//File: wav2sig.cpp
//Purpose: opens wavfile, maipulates data for use in the Array Toolbox
//Author: Grant Cox, University of Kentucky Distributed Audio Lab, grant.cox@uky.edu

#include "../include/wav2sig.hpp"

//////////////////////////////////////////////////////////////
//default destructor
wav2sig::wav2sig() {
    fs = 0;
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> paths) {
    fs = 0;
    num_files = paths.size();
    fnames = paths;

    read();
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> paths, int in_fs) {
    fs = in_fs;
    num_files = paths.size();
    fnames = paths;
    read();
    resample_signals();
}

//////////////////////////////////////////////////////////////

wav2sig::wav2sig(std::vector<std::string> paths, int in_fs, 
                 std::vector<float> tInt_in) {
    fs = in_fs;
    num_files = paths.size();
    fnames = paths;
    tInt = tInt_in;

    read();
    resample_signals();
    trimFile();
}

wav2sig::wav2sig(std::vector<std::string> paths,
                int in_fs,
                std::vector<float> in_tInt,
                std::vector<float> weights) {

    fs = in_fs;
    tInt = in_tInt;
    num_files = paths.size();
    fnames = paths;
    
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

uint8_t wav2sig::resample_signals() {
    std::vector<Col<double>> resampled_sigs(num_files);

    for(uint8_t i = 0; i < num_files; i++) {
        //convert the fs ratio into a p / q rational used in resampling
        if (fs != channel_fs[i]) {
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
        else
            throw invalid_argument("You entered an fs that was equal to the original.");
    }

    resize_filedata(resampled_sigs); //write new data out
    return 0;
}

//////////////////////////////////////////////////////////////
//

uint8_t wav2sig::trimFile() {
    vector<Col<double>> to_trim(num_files);
    for(int channel = 0; channel < num_files; channel++) {
        float time_index_1 = (float)channel_fs[channel] * tInt[0];
        float time_index_2 = (float)channel_fs[channel] * tInt[1];
        float num_samps = time_index_2 - time_index_1;

        int i1 = (int)time_index_1, i2 = (int)time_index_2;
        
        to_trim[channel] = zeros((int)num_samps);
        Col<double> old = filedata.col(channel);
        for(int j = i1; j < i2; j++)
            to_trim[channel](j - i1) = old(j); //the j - i1 avoids segfault due to diff sizes
    }
    resize_filedata(to_trim);
    return 0;
} //TODO test


//////////////////////////////////////////////////////////////


uint8_t wav2sig::multiplyWeight(vec in, std::vector<float> & weights) {
    return 0; //TODO
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

void wav2sig::resize_filedata(std::vector<Col<double>> & newData) {
    //now need to recreate filedata matrix to match resampled sigs
    for(int i = 0; i < num_files; i++)  
        samples_per_channel[i] = newData[i].size();
    std::vector<int>::iterator it;  //find new maximum size
    it = std::max_element(samples_per_channel.begin(), samples_per_channel.end());
    int max_samples = *it;
    
    //reset filedata
    filedata.zeros(max_samples, num_files);
    
    //put the data back
    for(int i = 0; i < num_files; i++)  filedata.col(i) = newData[i];
}