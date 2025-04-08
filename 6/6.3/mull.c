#include "header.h"

double mull(double *numbers) {
    double mul = 1;
    for(int iter = 0; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        mul *= numbers[iter];
    }
    return mul;
}
