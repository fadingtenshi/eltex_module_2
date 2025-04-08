#include "header.h"

int main() {

    User *arr = usersInit();

    printf("Welcome to phone directory!\n\n");
    char choice = 0;
    while(choice != '4') {
        printf("Enter command:\n[1] Add Contact\n[2] Delete Contact\n[3] Edit Contact\n[4] Exit program\n");
        choice = getchar();
        while(getchar() != '\n');
        if(choice == '1') {
            printf("Enter Name(must), Surname(must), Patronymic, Workplace and Email\n");
            char symbol;
            char fields[FIELDS_COUNT][BUFFER];
            int i = 0;
            bool latcherr = false;
            for(; i < FIELDS_COUNT; ++i) {
                int iter = 0;
                while ((symbol = getchar()) != '\n' && iter < BUFFER - 1) {
                    fields[i][iter++] = symbol;
                }
                fields[i][iter] = '\0';
                if (iter == 0 && (i == 0 || i == 1)) {
                    printf("Name or Surname must be entered!\n");
                    latcherr = true;
                    break;
                }
            }
            if(!latcherr) {
                char *fieldsPointer[FIELDS_COUNT];
                for(int i = 0; i < FIELDS_COUNT; ++i) fieldsPointer[i] = fields[i];
                addContact(arr, fieldsPointer);
            }
        }
        else if(choice == '2') {
            printf("Select id of contact to delete:\n");
            printContacts(arr);
            int id = getchar() - '0';
            char temp = 0;
            while((temp = getchar()) != '\n') { id *= 10; id += temp - '0'; }
            if(removeContact(&arr, id)) { printf("Invalid input!\n"); }
        }
        else if(choice == '3') {
            printf("Select id of contact to edit:\n");
            printContacts(arr);
            int id = getchar() - '0';
            char temp = 0;
            while((temp = getchar()) != '\n') { id *= 10; id += temp - '0'; }
            User *user = findNode(arr, id);
            if(user != NULL) {
                char fields[FIELDS_COUNT][BUFFER];
                for(int i = 0; i < FIELDS_COUNT; ++i) {
                    switch(i) {
                        case 0: printf("Enter changed name (empty for no changes): "); break;
                        case 1: printf("Enter changed surname (empty for no changes): "); break;
                        case 2: printf("Enter changed patronymic (empty for no changes): "); break;
                        case 3: printf("Enter changed workplace (empty for no changes): "); break;
                        case 4: printf("Enter changed email (empty for no changes): "); break;
                    }
                    int iter = 0;
                    while((temp = getchar()) != '\n') {
                        fields[i][iter++] = temp;
                    }
                    if(iter != 0) fields[i][iter] = '\0';
                }
                char *fieldsPointer[FIELDS_COUNT];
                for(int i = 0; i < FIELDS_COUNT; ++i) fieldsPointer[i] = fields[i];
                editContact(user, fieldsPointer);
            }
            else { printf("User not found!\n"); }
        }
    }
    clearList(arr);
    return 0;

}