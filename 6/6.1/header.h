
#ifndef HEADER

#define HEADER

#define BUFFER 128
#define FIELDS_COUNT 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

struct User {
    
    int id;
    char *name;
    char *surname;
    char *patronymic;
    char *workplace;
    char *email;

    struct User *prev;
    struct User *next;

};

typedef struct User User;

void allocFields(User *node);
User *usersInit();
void clearList(User *list);
void clearNode(User *list);

void insertData(User *list, char *fields[], int id);
User *findNode(User *list, int id);
bool addContact(User *list, char *fields[]);
void editContact(User *user, char **fields);
bool removeContact(User **list, int id);
void printContacts(User *list);

#endif