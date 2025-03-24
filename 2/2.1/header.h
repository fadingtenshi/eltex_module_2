
#ifndef HEADER

#define HEADER

#define BUFFER 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

typedef struct {
    int id;
    char *name;
    char *surname;
    char *patronymic;
    char *workplace;
    char *email;

} User;

typedef struct {
    User *arr;
} Users;

Users usersInit();
void clearmem(Users *arr);

bool addContact(Users *arr);
bool editContact(Users *arr, int id);
void removeContact(Users *arr, int id);

int *printContacts(Users *arr);

#endif