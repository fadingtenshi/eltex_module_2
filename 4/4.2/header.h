
#ifndef HEADER

#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

struct Node {
    uint8_t priority;
    int data;
    struct Node *next;
};

typedef struct Node Node;

void clearmem(Node *head);
void push(Node **head, uint8_t priority, int data);
Node *popFront(Node **head);
Node *popPriorityDot(Node *head, uint8_t priority);
Node *popPriorityGt(Node *head, uint8_t priority);
void printQueue(Node *head);


#endif