#include "header.h"

int main() {

    Users arr = usersInit();

    printf("Welcome to phone directory!\n\n");
    char choice = 0;
    while(choice != '4') {
        printf("Enter command:\n[1] Add Contact\n[2] Delete Contact\n[3] Edit Contact\n[4] Exit program\n");
        choice = getchar();
        while(getchar() != '\n');
        if(choice == '1') {
            printf("Enter Name(must), Surname(must), Patronymic, Workplace and Email\n");
            if(addContact(&arr)) printf("Name or Surname must be entered!\n");
        }
        else if(choice == '2') {
            printf("Select id of contact to delete:\n");
            int *ids = printContacts(&arr);
            int id = getchar() - '0';
            char temp = 0;
            while((temp = getchar()) != '\n') { id *= 10; id += temp - '0'; }
            int i = 0;
            for(; i < BUFFER && ids[i] != id; ++i);
            if(ids[i] == id) {
                removeContact(&arr, id);  
            }
            free(ids);
        }
        else if(choice == '3') {
            printf("Select id of contact to edit:\n");
            int *ids = printContacts(&arr);
            int id = getchar() - '0';
            char temp = 0;
            while((temp = getchar()) != '\n') { id *= 10; id += temp - '0'; }
            int i = 0;
            for(; i < BUFFER && ids[i] != id; ++i);
            if(ids[i] == id) {
                printf("Select params to edit:\n[0] - Exit;\n[1] - Name;\n[2] - Surname;\
\n[3] - Patronymic;\n[4] - Workplace;\n[5] - Email.\n");
                editContact(&arr, id);
            }
            free(ids);
        }
    }

    clearmem(&arr);
    return 0;

}