
#ifndef HEADER

#define HEADER
#define BUFFER 128
#define NUM_BUFFER 3
#define STR_BUFFER 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <ctype.h>

char *digToBit();
mode_t numToBit();
void printModebin(mode_t mode);
int *getModenum(mode_t mode);
char *getModestr(mode_t mode);

struct stat getFileStats();



#endif