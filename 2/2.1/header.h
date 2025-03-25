
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
    size_t size;
} Users;

Users usersInit();
void clearmem(Users *arr);

bool isUniqueId(Users *arr, int id);
bool addContact(Users *arr);
bool editContact(Users *arr, int id);
Users removeContact(Users *arr, int id);

int *printContacts(Users *arr);

#endif