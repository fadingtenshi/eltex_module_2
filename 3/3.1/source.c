
#include "header.h"

char *digToBit() {

    char digits[4];
    char *result = malloc(STR_BUFFER * sizeof(char));
    int count = 0;
    char symbol = 0;
    while((symbol = getchar()) != '\n') {
        if(isdigit(symbol)) {
            digits[count++] = symbol;
        }
    }

    digits[count] = '\0';
    int number = strtol(digits, NULL, 8);

    count = 0;
    for(int i = 8; i >= 0; i--) {
        result[count++] = (number >> i) & 1 ? '1' : '0';
    }
    result[count] = '\0';
    return result;

}

mode_t numToBit() {

    char digits[STR_BUFFER];
    int count = 0;  
    char symbol = 0;
    while((symbol = getchar()) != '\n' && count < 9) {
        if(symbol == 'r' || symbol == 'w' || symbol == 'x' || symbol == '-') {
            digits[count++] = symbol;
        }
    }
    digits[count] = '\0';

    mode_t mode = 0;

    digits[0] == 'r' ? mode |= S_IRUSR : 0;
    digits[1] == 'w' ? mode |= S_IWUSR : 0;
    digits[2] == 'x' ? mode |= S_IXUSR : 0;
    digits[3] == 'r' ? mode |= S_IRGRP : 0;
    digits[4] == 'w' ? mode |= S_IWGRP : 0;
    digits[5] == 'x' ? mode |= S_IXGRP : 0;
    digits[6] == 'r' ? mode |= S_IROTH : 0;
    digits[7] == 'w' ? mode |= S_IWOTH : 0;
    digits[8] == 'x' ? mode |= S_IXOTH : 0;

    return mode;

}

void printModebin(mode_t mode) {
    for(int i = 8; i >= 0; --i) {
        putchar(((1 << i) & mode) ? '1' : '0');
        if(i % 3 == 0) {
            putchar(' ');
        }
    }
    printf("\n");
}

int *getModenum(mode_t mode) {
    int *modeNum = calloc(NUM_BUFFER, sizeof(int));

    modeNum[0] |= mode & S_IRUSR ? 4 : 0;
    modeNum[0] |= mode & S_IWUSR ? 2 : 0;
    modeNum[0] |= mode & S_IXUSR ? 1 : 0;
    modeNum[1] |= mode & S_IRGRP ? 4 : 0;
    modeNum[1] |= mode & S_IWGRP ? 2 : 0;
    modeNum[1] |= mode & S_IXGRP ? 1 : 0;
    modeNum[2] |= mode & S_IROTH ? 4 : 0;
    modeNum[2] |= mode & S_IWOTH ? 2 : 0;
    modeNum[2] |= mode & S_IXOTH ? 1 : 0;

    return modeNum;
}

char *getModestr(mode_t mode) {
    char *modeStr = malloc(STR_BUFFER * sizeof(char));
    modeStr[0] = mode & S_IRUSR ? 'r' : '-';
    modeStr[1] = mode & S_IWUSR ? 'w' : '-';
    modeStr[2] = mode & S_IXUSR ? 'x' : '-';
    modeStr[3] = mode & S_IRGRP ? 'r' : '-';
    modeStr[4] = mode & S_IWGRP ? 'w' : '-';
    modeStr[5] = mode & S_IXGRP ? 'x' : '-';
    modeStr[6] = mode & S_IROTH ? 'r' : '-';
    modeStr[7] = mode & S_IWOTH ? 'w' : '-';
    modeStr[8] = mode & S_IXOTH ? 'x' : '-';
    modeStr[9] = '\0';

    return modeStr;
}


struct stat getFileStats() {
    char filepath[BUFFER];
    struct stat buf;
    char symbol = 0;
    u_int8_t count = 0;
    while((symbol = getchar()) != '\n') {
        filepath[count++] = symbol;
    }
    filepath[count] = '\0';
    stat(filepath, &buf);

    return buf;

}