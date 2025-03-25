
#include "header.h"

Users usersInit() {
    Users arr;
    arr.arr = NULL;
    arr.size = 0;
    return arr;
}

void clearmem(Users *arr) {
    for(size_t i = 0; i < arr->size; ++i) {
        free(arr->arr[i].name);
        free(arr->arr[i].surname);
        free(arr->arr[i].patronymic);
        free(arr->arr[i].workplace);
        free(arr->arr[i].email);
    }
    free(arr->arr);
}

bool isUniqueId(Users *arr, int id) {
    for (size_t j = 0; j < arr->size; j++) {
        if (arr->arr[j].id == id) {
            return false;
        }
    }
    return true;
}

bool addContact(Users *arr) {
    srand(time(NULL));
    int id;
    do {
        id = rand() % UINT16_MAX;
    } while (!isUniqueId(arr, id));
    User user;
    user.id = id;
    for (int i = 0; i < 5; ++i) {
        char *field = malloc(BUFFER);
        int iter = 0;
        char symbol;
        while ((symbol = getchar()) != '\n' && iter < BUFFER - 1) {
            field[iter++] = symbol;
        }
        field[iter] = '\0';
        if (iter == 0 && (i == 0 || i == 1)) {
            free(field);
            return 1;
        }
        switch (i) {
            case 0: user.name = field; break;
            case 1: user.surname = field; break;
            case 2: user.patronymic = field; break;
            case 3: user.workplace = field; break;
            case 4: user.email = field; break;
        }
    }
    if (arr->size == 0) {
        arr->arr = malloc(sizeof(User));
        arr->size = 1;
    } else {
        arr->arr = realloc(arr->arr, (arr->size + 1) * sizeof(User));
        arr->size++;
    }
    arr->arr[arr->size-1] = user;
    return 0;
}

bool editContact(Users *arr, int id) {
    char choice;
    size_t iter = 0;
    for(; iter < arr->size && arr->arr[iter].id != id; ++iter);
    if(iter == arr->size) return 1;
    void *fields[] = {&arr->arr[iter].name, &arr->arr[iter].surname, &arr->arr[iter].patronymic,
    &arr->arr[iter].workplace, &arr->arr[iter].email};
    while((choice = getchar()) > '0' && choice < '6') {
        char field = choice;
        int counter = 0;
        if(getchar() != '\n') return 1;
        while((choice = getchar()) != '\n') {
            (*(char **)fields[(field - '0')-1])[counter++] = choice;
        }
    }
    while(getchar() != '\n');
    return 0;
}

Users removeContact(Users *arr, int id) {
    size_t i = 0;
    for(; i < arr->size && arr->arr[i].id != id; ++i);
    free(arr->arr[i].name);
    free(arr->arr[i].surname);
    free(arr->arr[i].patronymic);
    free(arr->arr[i].workplace);
    free(arr->arr[i].email);
    for(; i < arr->size - 1; ++i) {
        arr->arr[i] = arr->arr[i+1];
    }
    Users temp;
    temp.size = --(arr->size);
    temp.arr = realloc(arr->arr, arr->size * sizeof(User));
    return temp;
}

int *printContacts(Users *arr) {
    int *ids = malloc(arr->size * sizeof(int));
    int iter = 0;
    for(size_t i = 0; i < arr->size; ++i) {
        if(arr->arr[i].name != NULL) {
            ids[iter++] = arr->arr[i].id;
            printf("[%d]: \"%s\", \"%s\", \"%s\", \"%s\", \"%s\"\n",\
            arr->arr[i].id, arr->arr[i].name, arr->arr[i].surname, arr->arr[i].patronymic,\
            arr->arr[i].workplace, arr->arr[i].email);
        }

    }
    return ids;
}