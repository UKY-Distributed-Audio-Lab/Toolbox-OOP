#include "HandyFunctions.h"

long gcd(long a, long b) {
    if (a == 0)
        return b;
    else if (b == 0)
        return a;

    if (a < b)
        return gcd(a, b % a);
    else
        return gcd(b, a % b);
}


mat resize_and_zero_pad(std::vector<Col<double>> & newData) {
    uint8_t cols = newData.size();
    
    //now need to recreate filedata matrix to match resampled sigs
    std::vector<int> sizes(cols);
    for(uint8_t i = 0; i < cols; i++)
        sizes[i] = newData[i].n_rows;
    
    //find the max number of samples
    uint32_t max_samples = find_max_vector_element(sizes);
    
    //reset filedata
    mat newMatrix = zeros(max_samples, cols);
    
    //put the data back
    for(int i = 0; i < cols; i++)  newMatrix.col(i) = newData[i];
}

//frequency sampling fir design
//https://www.allaboutcircuits.com/technical-articles/design-of-fir-filters-using-frequency-sampling-method/
vec fir2(int n_order, vec freq, vec mag) { 
    if(!(n_order % 2)) {
        fprintf(stderr,"ERROR in fir2: must request an odd-order FIR filter\n");
        exit(1);
    }
    if(freq.size() != n_order) {
        fprintf(stderr,"ERROR in fir2: size of vec freq does not equal the order requested\n");
        exit(1);
    }
    if(mag.size() != n_order) {
        fprintf(stderr,"ERROR in fir2: size of vec mag does not equal the order requested\n");
        exit(1);
    }


    int M = (n_order - 1) / 2;
    
    vec pos_coeffs(M+1); //coefficiencts from 0 to M
    vec pos_freq = freq.subvec(M, n_order-1);
    vec pos_mag  = mag.subvec(M, n_order-1); //subvector from 0 to max positive index
    vec h = zeros(n_order); //to return
    
    for(uint16_t n = 0; n <= M; n++) {
        float tmp_sum = 0;
        for(uint16_t k = 1; k <= M; k++)   {
            tmp_sum += pos_mag(k) * cos(n * pos_freq(k));
        }
        pos_coeffs(n) = (1/(2*(float)M+1)) * (pos_mag(0) + 2*tmp_sum);
    }
    
    //copy results to return variable h
    h(M) = pos_coeffs(0);
    uint16_t neg_index_offset = 2;
    for(uint16_t i = M+1; i < n_order; i++) {
        h(i) = pos_coeffs(i - M);
        h(i - neg_index_offset) = h(i);
        neg_index_offset += 2;
    }
    return h;
}

vec fill_vec_between_limits(int l1, int l2) {
    uint32_t size = std::abs(l2-l1) + 1;
    vec output(size);
    for(uint32_t i = 0; i < size; i++)
        output(i) = l1++;
    return output;
}
