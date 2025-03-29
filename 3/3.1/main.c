
#include "header.h"

mode_t toBinHandle() {
    
    char mode;
    mode_t bit_repr = 0;
    printf("Enter in which format the access rights will be entered:\n");
    printf("[1] - Digital\n");
    printf("[2] - Alphabetical\n");
    
    mode = getchar();
    while(getchar() != '\n');

    if(mode == '1') { 
        printf("Enter Digital access rights: ");
        bit_repr = digToBit();
    }
    else if(mode == '2') {
        printf("Enter Alphabetical access rights: ");              
        bit_repr = numToBit();
    }
    return bit_repr;
}

void printDifferModes(mode_t mode) {
    int *modeNum = getModenum(mode);
    printf("Digital representation: ");
    for(int i = 0; i < NUM_BUFFER; ++i) {
        printf("%d ", modeNum[i]);
    }
    printf("\n");
    printf("String representation: ");
    char *modeStr = getModestr(mode);
    for(int i = 0; i < STR_BUFFER; ++i) {
        printf("%c", modeStr[i]);
    }
    printf("\n\n");
    free(modeNum);
    free(modeStr);
}
int main() {

    char mode = 0;
    mode_t bit_repr = 0;
    mode_t bit_repr_change = 0;
    struct stat file_stats;

    while(mode != '0') {

        printf("Enter the number of the function you want to use:\n");
        printf("[0] - Exit program;\n");
        printf("[1] - Count bit representation;\n");
        printf("[2] - Show file's access rights;\n");
        printf("[3] - Change access rights.\n");
        printf("[4] - Print current access rights\n");
        mode = getchar();
        while(getchar() != '\n');

        if(mode == '1') {
            mode_t bit_repr_temp = toBinHandle();
            if(bit_repr_temp == 0) { printf("Invalid input!\n"); }
            else { bit_repr = bit_repr_temp; printModebin(bit_repr); }
        }
        else if(mode == '2') {

            printf("Enter path to file: ");
            file_stats = getFileStats();
            if(errno != 0) printf("Invalid input: %s\n", strerror(errno));
            else {
                bit_repr = file_stats.st_mode;
                printDifferModes(file_stats.st_mode);
            }
        }
        else if(mode == '3') {
            printf("Current mask:\n");
            printDifferModes(bit_repr);
            printf("Enter new mask to apply:\n");
            bit_repr_change = toBinHandle();
            if(bit_repr_change == 0) { printf("Invalid input!\n"); }
            else {
                printf("Enter \"+/-\" to change:\n");
                char action = getchar();
                while(getchar() != '\n');
                if(action == '+') { 
                    bit_repr |= bit_repr_change;
                }
                else if(action == '-') {
                    bit_repr &= ~bit_repr_change;
                }
                printf("New mask:\n");
                printDifferModes(bit_repr);
            }
        }
        else if(mode == '4') {
            printDifferModes(bit_repr);
        }

    }
    return 0;
}