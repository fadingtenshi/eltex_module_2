
#include "header.h"

Users usersInit() {

    Users arr;
    arr.arr = malloc(BUFFER * sizeof(User));
    for(int i = 0; i < BUFFER; ++i) {
        arr.arr[i].id = -1;
    }
    return arr;

}

void clearmem(Users *arr) {
    for(int i = 0; i < BUFFER; ++i) {
        free(arr->arr[i].name);
        free(arr->arr[i].surname);
        free(arr->arr[i].patronymic);
        free(arr->arr[i].workplace);
        free(arr->arr[i].email);
    }
    free(arr->arr);
}

bool addContact(Users *arr) {
    char symbol;
    int fields = 0;
    int i = 0;
    for(; i < BUFFER && arr->arr[i].name != NULL; ++i);
    srand(time(NULL));
    bool latch = false;
    int id = 0;
    while(!latch) {
        id = rand() % BUFFER;
        for(int j = 0; j < BUFFER; j++){
            if(arr->arr[j].id == id) break;
            if(j + 1 == BUFFER || arr->arr[j].name == NULL) {
                latch = true;
                break;
            }
        }
    }
    bool err = 0;
    while(fields < 5 && err != 1) {
        char *field = malloc(BUFFER * sizeof(char));
        int iter = 0;
        while((symbol = getchar()) != '\n' && iter < BUFFER) field[iter++] = symbol;
        arr->arr[i].id = id;
        if(fields == 0) {
            if(iter == 0) err = 1;
            else arr->arr[i].name = field;
        }
        else if(fields == 1) {
            if(iter == 0) err = 1;
            else arr->arr[i].surname = field;
        }
        else if(fields == 2) arr->arr[i].patronymic = field;
        else if(fields == 3) arr->arr[i].workplace = field;
        else if(fields == 4) arr->arr[i].email = field;
        fields++;
    }
    return err;
}

bool editContact(Users *arr, int id) {
    char choice;
    int i = 0;
    for(; arr->arr[i].id != id; i++){
        if(i + 1 == BUFFER) {;}
    }
    void *fields[] = {&arr->arr[i].name, &arr->arr[i].surname, &arr->arr[i].patronymic,
    &arr->arr[i].workplace, &arr->arr[i].email};
    while((choice = getchar()) != '0') {
        char field = choice;
        int counter = 0;
        if(getchar() != '\n') {
            while(getchar() != '\n');
            return 1;
        }
        while((choice = getchar()) != '\n') {
            (*(char **)fields[(field - '0')-1])[counter++] = choice;
        }
        printf("Print field to edit (0 - exit): ");
    }
    while(getchar() != '\n');
    return 0;
}

void removeContact(Users *arr, int id) {
    int i = 0;
    for(; i < BUFFER && arr->arr[i].id != id; ++i);
    free(arr->arr[i].name);
    free(arr->arr[i].surname);
    free(arr->arr[i].patronymic);
    free(arr->arr[i].workplace);
    free(arr->arr[i].email);
    arr->arr[i].id = -1;
    arr->arr[i].name = NULL;
    arr->arr[i].surname = NULL;
    arr->arr[i].workplace = NULL;
    arr->arr[i].email = NULL;
    if(i == 0) {
        arr->arr++;
        arr->arr = realloc(arr->arr, BUFFER * sizeof(User));
    }
}

int *printContacts(Users *arr) {
    int *ids = malloc(BUFFER * sizeof(int));
    int iter = 0;
    for(int i = 0; i < BUFFER; ++i) {
        if(arr->arr[i].name != NULL) {
            ids[iter++] = arr->arr[i].id;
            printf("[%d]: \"%s\", \"%s\", \"%s\", \"%s\", \"%s\"\n",\
            arr->arr[i].id, arr->arr[i].name, arr->arr[i].surname, arr->arr[i].patronymic,\
            arr->arr[i].workplace, arr->arr[i].email);
        }

    }
    return ids;
}