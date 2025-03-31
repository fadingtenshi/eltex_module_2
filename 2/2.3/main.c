
#include "header.h"

int main() {

    char choice = 0;

    Operation ops[] = {
            {'+', summ},
            {'-', subb},
            {'*', mull},
            {'/', divv}
    };

    printf("Welcome to a calculator!\n\n");
    while(choice != '0') {
        printf("Enter a action:\n[0] - Exit;\n[+] - Addition;\n[-] - Subtraction;\n[*] - Multiplication;\n[/] - Division\n");
        choice = getchar();
        if(choice == '0') {
            printf("Goodbye!\n");
            return 0;
        }
        while(getchar() != '\n');
        double *numbers;
        for(size_t i = 0; i < sizeof(ops) / sizeof(ops[0]); ++i) {
            if(ops[i].operator == choice) {
                printf("Enter two numbers, separated by space: ");
                numbers = getNumbers();
                if(numbers == NULL) {
                    free(numbers);
                    printf("Invalid input!\n");
                    return 1;
                }
                double number = ops[i].func(numbers);
                if(isnan(number)) { printf("Division by zero!\n"); }
                else { printf("Answer is: %lf\n", number); }
                free(numbers);
            }
        }
    }

}