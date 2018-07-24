//File: wav2sig.cpp
//Purpose: opens wavfile, maipulates data for use in the Array Toolbox
//Author: Grant Cox, University of Kentucky Distributed Audio Lab, grant.cox@uky.edu

#include "wav2sig.h"

//////////////////////////////////////////////////////////////
//default destructor
wav2sig::wav2sig() {}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> fnames_) {
    num_files = fnames_.size();
    fnames = fnames_;
    read();
}

//////////////////////////////////////////////////////////////


wav2sig::wav2sig(std::vector<std::string> fnames_, int fs_) {
    fs = fs_;
    num_files = fnames_.size();
    fnames = fnames_;
    read();
    resample_signals();
}

//////////////////////////////////////////////////////////////

wav2sig::wav2sig(std::vector<std::string> fnames_, std::vector<float> tInt_) {
    num_files = fnames_.size();
    fnames = fnames_;
    tInt = tInt_;
    read();
    trimFile();
}

wav2sig::wav2sig(std::vector<std::string> fnames_, std::vector<double> weights_) {
    num_files = fnames_.size();
    fnames = fnames_;
    weights = weights_;
    read();
    multiplyWeight();
}

wav2sig::wav2sig(std::vector<std::string> fnames_, 
                 int fs_, 
                 std::vector<float> tInt_) {
    
    fs = fs_;
    num_files = fnames_.size();
    fnames = fnames_;
    tInt = tInt_;

    read();
    trimFile();
    resample_signals();
}

wav2sig::wav2sig(std::vector<std::string> fnames_, 
                 int fs_, 
                 std::vector<double> weights_) {
    fs = fs_;
    num_files = fnames_.size();
    fnames = fnames_;
    weights = weights_;

    read();
    resample_signals();
    multiplyWeight();
}

wav2sig::wav2sig(std::vector<std::string> fnames_,
        std::vector<float> tInt_,
        std::vector<double> weights_) {

    num_files = fnames_.size();
    fnames = fnames_;
    tInt = tInt_;
    weights = weights_;

    read();
    trimFile();
    multiplyWeight();
}

wav2sig::wav2sig(std::vector<std::string> fnames_,
                int fs_,
                std::vector<float> tInt_,
                std::vector<double> weights_) {

    fs = fs_;
    tInt = tInt_;
    num_files = fnames_.size();
    fnames = fnames_;
    weights = weights_;
    
    read();
    trimFile();
    resample_signals();
    multiplyWeight();
}

//////////////////////////////////////////////////////////////

void wav2sig::read() {
    uint8_t count = 0;
    int max_samples = 0;
    std::vector<AudioFile<double>> fdata(num_files); //hold raw samples
    //iterate through the filenames
    for (std::vector<std::string>::iterator i = fnames.begin(); i != fnames.end(); ++i) {
        fdata[count].load(*i);   //load the audio samples into the vector index

        cout << "Loaded " << *i << endl;
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
            double fs_ratio      = fs / channel_fs[i];
            double integral      = std::floor(fs_ratio);
            double frac          = fs_ratio - integral;
            const long precision = 1000000000; // This is the accuracy.

            long gcd_ = gcd(round(frac * precision), precision);

            long denominator = precision / gcd_;
            long numerator   = round(frac * precision) / gcd_;
            numerator       += integral * denominator;
            
            //having the numerator and he denominator, use the resampling class to resample with fir
            //anti-aliasing at ratio p/q or numerator/denominator
            Col<double> to_process = filedata.col(i);
            Col<double> processed  = zeros<Col<double>>(to_process.n_rows * numerator / denominator);
            
            sp::resampling<double> sampler(numerator, denominator); //make resampler
            sampler.upfirdown(to_process,processed);                //resample

            resampled_sigs[i] = processed;             //put into resampled vector
            channel_fs[i] = fs;                        //note new fs for each file
            samples_per_channel[i] = processed.size(); //update samps per channel
        }
        else
            throw invalid_argument("You entered an fs that was equal to the original.");
    }

    resize_filedata(resampled_sigs); //write new data out
    return 0;
}

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


uint8_t wav2sig::multiplyWeight() {
    mat dev = stddev(abs(filedata));
    double normme = 0.0;

    for(uint8_t i = 0; i < num_files; i++)      normme += dev(0,i);
    normme /= num_files;

    filedata /= 10 * normme;

    for(uint8_t i = 0; i < num_files; i++)      filedata.col(i) *= weights[i];
    return 0;
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

void wav2sig::write() {
    //iterate over each file
    for(uint8_t i = 0; i < num_files; i++) {
        //initialize audiofile with one channel, right number of samples, fs
        AudioFile<double> fileOut;
        fileOut.setAudioBufferSize(1, filedata.col(i).n_rows);
        fileOut.setSampleRate(channel_fs[i]);
        
        //iterate over all samples in the file
        for(int j = 0; j < filedata.col(i).n_rows; j++)
            fileOut.samples[0][j] = filedata(j,i);

        fileOut.printSummary();
        
        string path = "./out" + to_string(i) + ".wav";
        fileOut.save(path);
    }
    printf("Wrote all files\n\r");
}