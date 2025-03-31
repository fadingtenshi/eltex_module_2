
#include "header.h"

double summ(double *numbers) {
    double sum = 0;
    for(int iter = 0; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        sum += numbers[iter];
    }
    return sum;
}

double subb(double *numbers) {
    int iter = 0;
    double sub = numbers[iter++];
    for(; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        sub -= numbers[iter];
    }
    return sub;
}

double mull(double *numbers) {
    double mul = 1;
    for(int iter = 0; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        mul *= numbers[iter];
    }
    return mul;
}

double divv(double *numbers) {
    int iter = 0;
    double div = numbers[iter++];
    for(; iter < BUFFER && !isnan(numbers[iter]); ++iter) {
        if(numbers[iter] != 0) div /= numbers[iter];
        else {
            return NAN;
        }
    }
    return div;
}


int gatherNumber(char *numbers) {
    int gatheredNumbers = 0;
    int iter_1 = 0;
    gatheredNumbers += numbers[iter_1++];
    while(numbers[iter_1] != 0) {
        gatheredNumbers *= 10;
        gatheredNumbers += numbers[iter_1++];
    }
    return gatheredNumbers;
}

double *getNumbers() {
    char symbol = 0;
    double *numbers = malloc(BUFFER * sizeof(double));
    int iter_1 = 0;
    int iter_2 = 0;
    char temp_arr[BUFFER][BUFFER];
    memset(temp_arr, 0, sizeof(temp_arr));
    while(symbol != '\n') {
        symbol = getchar();
        if((symbol >= '0' && symbol <= '9') || symbol == '.') temp_arr[iter_1][iter_2++] = symbol;
        else if((symbol == ' ' && strlen(temp_arr[iter_1]) > 0) || symbol == '\n') {
            temp_arr[iter_1++][iter_2] = '\0';
            iter_2 = 0;
        }
        else return NULL;
    }
    iter_1 = 0;
    for(; iter_1 < BUFFER && temp_arr[iter_1][0] != 0; ++iter_1) {
        numbers[iter_1] = strtod(temp_arr[iter_1], NULL);
    }
    numbers[iter_1] = NAN;
    return numbers;
}