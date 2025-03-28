
#include "header.h"

int main() {

    char mode_1 = 0;
    char mode_2 = 0;
    char *bit_repr_1 = 0;
    mode_t bit_repr_2 = 0;
    struct stat file_stats;

    while(mode_1 != '0') {

        printf("Enter the number of the function you want to use:\n");
        printf("[0] - Exit program;\n");
        printf("[1] - Count bit representation;\n");
        printf("[2] - Show file's access rights;\n");
        printf("[3] - Change access rights.\n");
        mode_1 = getchar();
        while(getchar() != '\n');

        if(mode_1 == '1') {
            
            printf("Enter in which format the access rights will be entered:\n");
            printf("[1] - Digital\n");
            printf("[2] - Alphabetical\n");
            
            mode_2 = getchar();
            while(getchar() != '\n');

            if(mode_2 == '1') { 
                printf("Enter Digital access rights: ");
                bit_repr_1 = digToBit();
                printf("%s\n", bit_repr_1);
            }
            else if(mode_2 == '2') {
                printf("Enter Alphabetical access rights: ");              
                bit_repr_2 = numToBit();
                printModebin(bit_repr_2);
            }
        }
        else if(mode_1 == '2') {

            printf("Enter path to file: ");
            file_stats = getFileStats();

            printf("\nBinary representation: ");
            printModebin(file_stats.st_mode);
            int *modeNum = getModenum(file_stats.st_mode);
            printf("Digital representation: ");
            for(int i = 0; i < NUM_BUFFER; ++i) {
                printf("%d ", modeNum[i]);
            }
            printf("\n");
            printf("String representation: ");
            char *modeStr = getModestr(file_stats.st_mode);
            for(int i = 0; i < STR_BUFFER; ++i) {
                printf("%c", modeStr[i]);
            }
            printf("\n\n");
            free(modeNum);
            free(modeStr);
        }

    }
    free(bit_repr_1);
    return 0;
}