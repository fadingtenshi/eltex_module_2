
#include "header.h"


void clearmem(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}

void push(Node **head, uint8_t priority, int data) {
    Node *temp = *head;
    Node *prev = NULL;
    while (temp != NULL) {
        if (temp->priority > priority) {
            Node *insert = malloc(sizeof(Node));
            insert->priority = priority;
            insert->data = data;
            insert->next = temp;
            if (prev == NULL) {
                *head = insert;
            } else {
                prev->next = insert;
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    
    Node *insert = malloc(sizeof(Node));
    insert->priority = priority;
    insert->data = data;
    insert->next = NULL;
    if (prev == NULL) {
        *head = insert;
    } else {
        prev->next = insert;
    }
}


Node *popFront(Node **head) {
    if (*head == NULL) {
        return NULL;
    }
    
    Node *temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    return temp;
}


Node *popPriorityDot(Node *head, uint8_t priority) {
    Node *temp = head;
    Node *prev = NULL;
    while (temp != NULL) {
        if (temp->priority == priority) {
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        return NULL;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    temp->next = NULL;
    return temp;
}


Node *popPriorityGt(Node *head, uint8_t priority) {
    Node *temp = head;
    Node *prev = NULL;
    while (temp != NULL) {
        if (temp->priority >= priority) {
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        return NULL;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    temp->next = NULL;
    return temp;
}

void printQueue(Node *head) {
    int count = 1;
    printf("Count - Priority - Data\n");
    while (head != NULL) {
        printf("%d\t[%d]\t[%d]\n", count++, head->priority, head->data);
        head = head->next;
    }
}