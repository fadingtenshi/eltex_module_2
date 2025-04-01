
#include "header.h"

void getMode(Node *queue, Node *(*func)(Node*, uint8_t)) {
    uint8_t priority = 0;
    char symbol = 0;
    printf("Enter priority (0-255) : ");
    priority = (uint8_t)(getchar() - '0');
    while((symbol = getchar()) != '\n') { priority *= 10; priority += symbol - '0'; }
    Node *output = func(queue, priority);
    if(output != NULL) printf("Priority: [%d]\nData: [%d]\n", output->priority, output->data);
    else printf("Priority not found!\n");
    free(output);
}

int main(void) {

    Node *queue;

    srand(time(NULL));

    char mode = 0;

    while(mode != '4') {
        printf("Enter mode:\n[1] - Add data (random);\n[2] - Get data;\n[3] - Print list;\n[4] - Exit program\n");
        mode = getchar();
        while(getchar() != '\n');
        if(mode == '1') {
            char symbol = 0;
            printf("Enter random count: ");
            int r_count = getchar() - '0';
            while((symbol = getchar()) != '\n') { r_count *= 10; r_count += symbol - '0'; }
            for(int i = 0; i < r_count; ++i) {
                push(&queue, (uint8_t)((rand() % 255)+1), rand());
            }
        }
        else if(mode == '2') {
            printf("Enter mode of printing:\n[1] - Queue's head;\n[2] - Precisely priority;\n[3] - Greater than priority.\n");
            char mode_2 = getchar();
            while(getchar() != '\n');
            if(mode_2 == '1') {
                Node *output = popFront(&queue);
                printf("Priority: [%d]\nData: [%d]\n", output->priority, output->data);
                free(output);
            }
            else if(mode_2 == '2') {
                getMode(queue, popPriorityDot);
            }
            else if(mode_2 == '3') {
                getMode(queue, popPriorityGt);
            }
        }
        else if(mode == '3') {
            printQueue(queue);
        }
    }
    clearmem(queue);
    return 0;
}