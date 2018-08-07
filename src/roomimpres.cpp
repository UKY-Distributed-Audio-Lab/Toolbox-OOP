#include "roomimpres.h"

impres roomimpres(vec &dlays, vec &scls, double &c, int &fs) {
    sfac mysfac;
    vec frequency = zeros(201);
    for(uint8_t i = 0; i < frequency.n_rows; i++)
        frequency(i) = i;
    mysfac.freq = (fs/2) * frequency/200;
    //create attenuation values with nominal temperature, humidity and pressure
    uint8_t temp = 22;      //deg C
    float pressure = 29.92; //Hg
    uint8_t humidity = 38;  //percent
    uint8_t distance = 1;   //meters
    mysfac.atten = atmAtten(temp, pressure, humidity, distance, mysfac.freq);

    mysfac.freq.print();
    mysfac.atten.print();
    
    return roomimpres(dlays, scls, c, fs, mysfac);
}

impres roomimpres(vec &dlays, vec &scls, double &c, int &fs, sfac sfac_in) {
    //The frequeny range must extend from 0 to fs/2 to be compatable with FIR2
    if(sfac_in.freq(0) != 0) {
        vec temp = zeros(sfac_in.freq.n_rows + 1);   //extend to 0 w/ nearest neighbor value
        temp.rows(1,temp.n_rows) = sfac_in.freq;
        sfac_in.freq = temp;
        sfac_in.freq.print();
        
        temp = zeros(sfac_in.atten.n_rows + 1);
        temp(0) = sfac_in.atten(0); 
        temp.rows(1,temp.n_rows) = sfac_in.atten;
        sfac_in.atten.print();
    }
    if(sfac_in.freq(sfac_in.freq.n_rows - 1) != fs/2) {
        //extend to fs/2 w/ nearest neighbor value
        vec temp = { (double)fs / 2 };
        sfac_in.freq.insert_rows(sfac_in.freq.n_rows, temp);
        sfac_in.freq.print();
        
        temp = sfac_in.atten(sfac_in.atten.n_rows - 1);
        sfac_in.atten.insert_rows(sfac_in.atten.n_rows, temp);
        sfac_in.atten.print();
    }

    int len = 50; //minimum fir filter length
    vec nfax = sfac_in.freq/(fs/2); //normalized frequency axis for FIR filter
    int mxdly = ceil(dlays.max() * fs); //max delay in samples

    //Find filter spectral spread to determine time support for
    //freqsp = sum(sfac.freq.*10.^(-sfac.atten/20))/sum(10.^(-sfac.atten/20));
    double freqsp = sum(sfac_in.freq % exp10(-sfac_in.atten/20)) / sum(exp10(-sfac_in.atten/20));
    double mxsprd = 1 / freqsp; //reciprocal of frequency at spread point (s)

    impres to_return;
    to_return.response = zeros(ceil(5*fs*mxsprd+mxdly));

    //  Loop through each delay and assign impulse response corresponding to
    //  image/multipath scatterer at that delay
    for(uint8_t k = 0; k < dlays.n_rows; k++) {
        double d = dlays(k) * c;        //distance traveled by signal
        vec attn = d * sfac_in.atten;   //log slope of spectrum
        double dt = abs(5* mxsprd);     //spread in time domain ( 5 time constants )
        int filn = round(dt * fs);

        //if time domain spread is less than len samples, set equal to len (length of sample spectra)
        if( filn < len ) 
            filn = len;
        else if (filn > fs/2)
            filn = fs/2;

        //if filter order is not even, increase by one sample to make even
        if(filn % 2 != 0)
            filn++;
        
        //compute frequency spectrum for attenuation
        vec alph = exp10(-attn/20);
    }

    return to_return;
}