#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    vec freq(25);
    freq(12) = 0; //0 point of frequency
    uint8_t neg_side_offset = 2;
    for(int i = 13; i < 25; i++) { //create 25 order fir 
        //12 on each side of 0
        freq(i) = neg_side_offset * M_PI / 25;
        freq(i - neg_side_offset) = -freq(i);
        neg_side_offset += 2;
    }
    printf("freq:\n");  freq.print();

    vec mag = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    printf("mag:\n"); mag.print();
    uint8_t order = 25;

    vec h = fir2(order, freq, mag);
    printf("\nh:\n");
    h.print();
}