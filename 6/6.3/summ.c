#include "header.h"

double summ(double *numbers) {
    double sum = 0;
    for(int iter = 0; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        sum += numbers[iter];
    }
    return sum;
}