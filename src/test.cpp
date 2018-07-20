#define unix

#include "../libs/armadillo"
#include "../libs/sigpack/sigpack.h"
#include <stdio.h>


using namespace arma;

int main() {
	Col<double> original = {.2, .3, .4, .5, .6};
	for(int i = 0; i < original.size(); i++)
		printf("%f\t",original(i));
	printf("\n\r");
	Col<double> upsampled = sp::upsample(original, 3);
	for(int i = 0; i < upsampled.size(); i++)
		printf("%f\t",upsampled(i));
	printf("\n\r");
	Col<double> downsampled = sp::downsample(upsampled,2);
	for(int i = 0; i < downsampled.size(); i++)
		printf("%f\t",downsampled(i));
	printf("\n\r");

	printf("length original: %d\n\rlength upsampled: %d\n\rlength down: %d\n\r",
				original.size(), upsampled.size(), downsampled.size());
	return 0;
}
