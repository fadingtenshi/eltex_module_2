
#include "header.h"

void allocFields(User *node) {
    node->name = malloc(BUFFER * sizeof(char));
    node->surname = malloc(BUFFER * sizeof(char));
    node->patronymic = malloc(BUFFER * sizeof(char));
    node->workplace = malloc(BUFFER * sizeof(char));
    node->email = malloc(BUFFER * sizeof(char));
    node->prev = NULL;
    node->next = NULL;
}

User *usersInit() {
    User *list = malloc(sizeof(User));
    return list;
}

void clearList(User *list) {
    
    User *curr = list;
    while(curr != NULL) {
        User *next = curr->next;
        clearNode(curr);
        curr = next;
    }

}

void clearNode(User *list) {
    free(list->name);
    free(list->surname);
    free(list->patronymic);
    free(list->workplace);
    free(list->email);
    free(list);
}

void insertData(User *list, char *fields[], int id) {
    list->id = id;
    list->name = strdup(fields[0]);
    list->surname = strdup(fields[1]);
    list->patronymic = strdup(fields[2]);
    list->workplace = strdup(fields[3]);
    list->email = strdup(fields[4]);
}

User *findNode(User *list, int id) {
    User *temp = list;

    while(temp != NULL) {
        if(temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

bool addContact(User *list, char *fields[]) {
    User *temp = list;
    int id = 1;
    if (temp->id == 0) {
        insertData(temp, fields, id);
        return 0;
    }
    while (temp->next != NULL) {
        if (temp->id != id) {
            break;
        }
        temp = temp->next;
        ++id;
    }

    if(temp->next == NULL && temp->id == id) {
        User *insert = usersInit();
        insertData(insert, fields, ++id);
        temp->next = insert;
        insert->prev = temp;
    }
    else {
        User *insert = usersInit();
        insertData(insert, fields, id);
        User *prev = temp->prev;
        prev->next = insert;
        temp->prev = insert;
        insert->prev = prev;
        insert->next = temp;
    }

    return 0;
}

void editContact(User *user, char **field) {

    void *fields[] = { &user->name, &user->surname, &user->patronymic, &user->workplace, &user->email };
    for(int i = 0; i < FIELDS_COUNT; ++i) {
        if(field[i][0] != '\0') {
            free(*(char**)fields[i]);
            *(char**)fields[i] = strdup(field[i]);
        }
    }

}

bool removeContact(User **list, int id) {

    User *temp = *list;
    while(temp != NULL) {
        if(temp->id == id) {
            break;
        }
        temp = temp->next;
    }
    
    if(temp == NULL) {
        return false;
    }

    if(temp->prev == NULL) {
        *list = temp->next;
        if (*list != NULL) {
            (*list)->prev = NULL; 
        }
    } else {
        User *prev = temp->prev;
        User *next = temp->next;
        if(next != NULL) {
            next->prev = prev;
        }
        prev->next = next;
    }

    clearNode(temp);
    return false;
}

void printContacts(User *list) {
    User *temp = list;
    while (temp != NULL) {
        printf("[%d]: \"%s\", \"%s\", \"%s\", \"%s\", \"%s\"\n", temp->id,
        temp->name, temp->surname, temp->patronymic, temp->workplace, temp->email);
        temp = temp->next;
    }
}
