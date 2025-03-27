
#include "header.h"

int main() {

    char choice = 0;

    printf("Welcome to a calculator!\n\n");
    while(choice != '0') {
        printf("Enter a action:\n[0] - Exit;\n[1] - Addition;\n[2] - Subtraction;\n[3] - Multiplication;\n[4] - Division\n");
        choice = getchar();
        if(choice == '0') return 0;
        while(getchar() != '\n');
        printf("Enter two numbers, separated by space: ");
        double *numbers = getNumbers();
        if(numbers == NULL) {
            free(numbers);
            printf("Invalid input!\n");
            return 1;
        }
        switch(choice) {
            case '1': printf("Answer is: %lf\n", summ(numbers)); break;
            case '2': printf("Answer is: %lf\n", subb(numbers)); break;
            case '3': printf("Answer is: %lf\n", mull(numbers)); break;
            case '4': printf("Answer is: %lf\n", divv(numbers)); break;
            default: free(numbers); return 1;
        }
        free(numbers);
    }

}