#ifndef HEADER
#define HEADER

#define BUFFER 128

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char operator;
    double (*func)(double*);
    void *handle;
} Operation;

int gatherNumber(char *numbers);
double *getNumbers();

#endif