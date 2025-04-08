#include "header.h"
#include <dlfcn.h>
#include <dirent.h>

int main() {
    Operation ops[4];
    int op_count = 0;
    DIR *dir = opendir(".");
    if (!dir) {
        perror("Cannot open directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && op_count < 4) {
        if (strstr(entry->d_name, ".so") != NULL) {
            char *lib_path = malloc(strlen(entry->d_name) + 3);
            sprintf(lib_path, "./%s", entry->d_name);

            void *handle = dlopen(lib_path, RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "Cannot open library %s: %s\n", lib_path, dlerror());
                free(lib_path);
                continue;
            }

            char *func_name = strdup(entry->d_name + 3);
            func_name[strlen(func_name) - 3] = '\0';

            double (*func)(double*) = dlsym(handle, func_name);
            char *error = dlerror();
            if (error) {
                fprintf(stderr, "Cannot load function %s: %s\n", func_name, error);
                dlclose(handle);
                free(func_name);
                free(lib_path);
                continue;
            }

            char operator;
            if (strcmp(func_name, "summ") == 0) operator = '+';
            else if (strcmp(func_name, "subb") == 0) operator = '-';
            else if (strcmp(func_name, "mull") == 0) operator = '*';
            else if (strcmp(func_name, "divv") == 0) operator = '/';
            else {
                fprintf(stderr, "Unknown function %s\n", func_name);
                dlclose(handle);
                free(func_name);
                free(lib_path);
                continue;
            }

            ops[op_count].operator = operator;
            ops[op_count].func = func;
            ops[op_count].handle = handle;
            op_count++;

            free(func_name);
            free(lib_path);
        }
    }
    closedir(dir);

    if (op_count == 0) {
        printf("No operations loaded.\n");
        return 1;
    }

    printf("Welcome to a calculator!\n\n");
    char choice = 0;
    while (choice != '0') {
        printf("Enter an action:\n[0] - Exit;\n");
        for (int i = 0; i < op_count; i++) {
            printf("[%c] - %s;\n", ops[i].operator,
                   ops[i].operator == '+' ? "Addition" :
                   ops[i].operator == '-' ? "Subtraction" :
                   ops[i].operator == '*' ? "Multiplication" : "Division");
        }
        choice = getchar();
        if (choice == '0') {
            printf("Goodbye!\n");
            break;
        }
        while (getchar() != '\n');

        int op_index = -1;
        for (int i = 0; i < op_count; i++) {
            if (ops[i].operator == choice) {
                op_index = i;
                break;
            }
        }

        if (op_index == -1) {
            printf("Invalid operation!\n");
            continue;
        }

        printf("Enter numbers separated by spaces: ");
        double *numbers = getNumbers();
        if (numbers == NULL) {
            printf("Invalid input!\n");
            continue;
        }

        double result = ops[op_index].func(numbers);
        if (isnan(result)) {
            printf("Division by zero!\n");
        } else {
            printf("Answer is: %.2f\n", result);
        }
        free(numbers);
    }

    for (int i = 0; i < op_count; i++) {
        dlclose(ops[i].handle);
    }

    return 0;
}