#include "delay.h"


//   This function delays the signal in vector S sampled at FS by an amount
//   D denoted in seconds.  If NS is present in the input argument,
//   the output signal length will be equal to this value in seconds (either by
//   truncating or zero padding).  If not present, the output signal length
//   will vary depending on the delay (it will be the original
//   signal length plus the max delay rounded up to the next sample).

//     [sd, tn] = delayt(s,fs,d,ns)

//   The delayed version of the signal SD starts at the same time point (D should
//   not be negative otherwise an error will occur).  This version performs the delay
//   in the time domain with an FIR shifting (interpolation) filter.  The FIR
//   interpolation filter is a 4-th order weighted SINC function, the default
//   weighting window is the cosine square (one of my favorites).  Comments
//   can be changed inside code to activate different windowing options.
//   IF TN is present in the output, a time axis is created for the output array
//   where 0 denotes the original starting point for S.
//   If S is a matrix, the program will assume each column is a signal and
//   the number of elements in D must be equal to the number of columns.
mat delayt(mat sigin, uint32_t fs, std::vector<float> delay_samples) {
    if(delay_samples.size() != sigin.n_cols)
        throw invalid_argument("Size of delay_samples does not match size of sigin.\n\r");
    if(fs <= 0)
        throw invalid_argument("Cannot have fs <= 0.\n\r");

    
    uint8_t order_ceiling = ceil(FILTER_ORDER / 2);
    std::vector<int8_t> sinc_grid;
    for(int8_t i = -order_ceiling + 1; i <= order_ceiling; i++)     
        sinc_grid.push_back(i);
    
    
    //compute number of samples to delay based on delay_samples
    std::vector<uint32_t> delay_samples(delay_samples.size());
    for(uint8_t i = 0; i < delay_samples.size(); i++)   
        delay_samples[i] = fs * delay_samples[i];

    //find signal length of output matrix
    uint32_t signal_length = find_max_vector_element(delay_samples) + sigin.n_rows;

    mat dummy_integer_shift = zeros(signal_length + FILTER_ORDER, 1);
    mat              output = zeros(signal_length, sigin.n_cols);
    
}