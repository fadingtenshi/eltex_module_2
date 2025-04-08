#ifndef HEADER
#define HEADER

#define BUFFER 128
#define FIELDS_COUNT 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

struct User {
    int id;
    char *name;
    char *surname;
    char *patronymic;
    char *workplace;
    char *email;
};

typedef struct User User;

struct Node {
    User user;
    struct Node* left;
    struct Node* right;
    int height;
};

typedef struct Node Node;

void allocFields(User *node);
Node* createNode(User user);
int getHeight(Node* node);
int getBalance(Node* node);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
Node* balanceNode(Node* node);
Node* insertNode(Node* node, User user);
int findMinFreeID(Node* root);
Node* findNode(Node* root, int id);
Node* deleteNode(Node* root, int id);
void printTree(Node* root);
void freeTree(Node* root);
bool addContact(Node** root, char *fields[]);
void editContact(Node* userNode, char **fields);
bool removeContact(Node** root, int id);
void printContacts(Node* root);
void printTreeAsTree(Node* root, int depth);

#endif