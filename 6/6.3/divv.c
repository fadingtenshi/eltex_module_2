#include "header.h"

double divv(double *numbers) {
    int iter = 0;
    double div = numbers[iter++];
    for(; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        if(numbers[iter] != 0) div /= numbers[iter];
        else { return NAN; }
    }
    return div;
}
