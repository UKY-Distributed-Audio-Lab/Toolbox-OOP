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
    printf("freq:\n"); freq.print(); 
    printf("mag:\n"); mag.print();
    int M = (n_order - 1) / 2;
    vec pos_coeffs(M+1); //coefficiencts from 0 to M
    vec h;

    for(uint16_t n = 0; n <= M; n++) {
        int tmp_sum = 0;
        for(uint16_t k = 1; k <= M; k++)   {
            printf("%d += %f * cos(%d * %f)\n", tmp_sum, mag(k), n, freq(k));
            tmp_sum += mag(k) * cos(n * freq(k));
        }
        printf("pos_coeffs(%d) = (1/(2*%d+1)) * (%d + 2*%f\n\n", n, M, mag(0), tmp_sum);
        pos_coeffs(n) = (1/(2*(float)M+1)) * (mag(0) + 2*tmp_sum);
    }
    printf("\npos_coeffs:\n"); pos_coeffs.print();
    return h;
}

vec fill_vec_between_limits(int l1, int l2) {
    uint32_t size = std::abs(l2-l1) + 1;
    vec output(size);
    for(uint32_t i = 0; i < size; i++)
        output(i) = l1++;
    return output;
}