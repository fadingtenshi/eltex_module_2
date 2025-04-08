#include "header.h"

double subb(double *numbers) {
    int iter = 0;
    double sub = numbers[iter++];
    for(; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        sub -= numbers[iter];
    }
    return sub;
}