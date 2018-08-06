#include <string>
#include "ArrayToolbox.h"


int main(int argc, char* argv[]) {
    mat micplane = { {0, 0, 2.1},
                     {0, 3.6, 2.1},
                     {3.6, 3.6, 2.1}};
    micplane.print();
    micplane = micplane.t(); //transpose
    micplane.print();

    double micspacing = 1.3;
    bool rectangle = true;
    
    mat plane = regmicsplane(micplane, micspacing, rectangle);
    plane.print();
    return 0;
}