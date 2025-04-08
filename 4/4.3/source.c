#include "header.h"

void allocFields(User *node) {
    node->name = malloc(BUFFER * sizeof(char));
    node->surname = malloc(BUFFER * sizeof(char));
    node->patronymic = malloc(BUFFER * sizeof(char));
    node->workplace = malloc(BUFFER * sizeof(char));
    node->email = malloc(BUFFER * sizeof(char));
}

Node* createNode(User user) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->user = user;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getHeight(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

Node* balanceNode(Node* node) {
    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    if (balance < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

Node* insertNode(Node* node, User user) {
    if (node == NULL) return createNode(user);

    if (user.id < node->user.id) {
        node->left = insertNode(node->left, user);
    } else if (user.id > node->user.id) {
        node->right = insertNode(node->right, user);
    } else {
        return node;
    }

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    return balanceNode(node);
}

void collectIDs(Node* root, bool* usedIDs, int* maxID) {
    if (root == NULL) return;

    if (root->user.id > *maxID) *maxID = root->user.id;
    if (root->user.id > 0) usedIDs[root->user.id] = true;

    collectIDs(root->left, usedIDs, maxID);
    collectIDs(root->right, usedIDs, maxID);
}

int findMinFreeID(Node* root) {
    if (root == NULL) return 1;
    int maxID = 0;
    bool* usedIDs = (bool*)calloc(10001, sizeof(bool));
    if (usedIDs == NULL) return -1;
    collectIDs(root, usedIDs, &maxID);
    int newID = 1;
    while (newID <= maxID + 1 && usedIDs[newID]) {
        newID++;
    }
    free(usedIDs);
    return newID;
}

Node* findNode(Node* root, int id) {
    if (root == NULL || root->user.id == id) return root;

    if (id < root->user.id) return findNode(root->left, id);
    return findNode(root->right, id);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}

Node* deleteNode(Node* root, int id) {
    if (root == NULL) return root;

    if (id < root->user.id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->user.id) {
        root->right = deleteNode(root->right, id);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->user = temp->user;
        root->right = deleteNode(root->right, temp->user.id);
    }

    if (root == NULL) return root;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    return balanceNode(root);
}

void printTree(Node* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("[%d]: \"%s\", \"%s\", \"%s\", \"%s\", \"%s\"\n", root->user.id,
               root->user.name, root->user.surname, root->user.patronymic, root->user.workplace, root->user.email);
        printTree(root->right);
    }
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->user.name);
        free(root->user.surname);
        free(root->user.patronymic);
        free(root->user.workplace);
        free(root->user.email);
        free(root);
    }
}

bool addContact(Node** root, char *fields[]) {
    User user;
    user.id = findMinFreeID(*root);

    if (user.id == -1) return 1;

    user.name = strdup(fields[0]);
    user.surname = strdup(fields[1]);
    user.patronymic = strdup(fields[2]);
    user.workplace = strdup(fields[3]);
    user.email = strdup(fields[4]);

    *root = insertNode(*root, user);
    return 0;
}

void editContact(Node* userNode, char **fields) {
    if (fields[0][0] != '\0') { free(userNode->user.name); userNode->user.name = strdup(fields[0]); }
    if (fields[1][0] != '\0') { free(userNode->user.surname); userNode->user.surname = strdup(fields[1]); }
    if (fields[2][0] != '\0') { free(userNode->user.patronymic); userNode->user.patronymic = strdup(fields[2]); }
    if (fields[3][0] != '\0') { free(userNode->user.workplace); userNode->user.workplace = strdup(fields[3]); }
    if (fields[4][0] != '\0') { free(userNode->user.email); userNode->user.email = strdup(fields[4]); }
}

bool removeContact(Node** root, int id) {
    *root = deleteNode(*root, id);
    return (*root == NULL && id != 0) ? 1 : 0;
}

void printContacts(Node* root) {
    printTree(root);
}

void printTreeAsTree(Node* root, int depth) {
    if (root == NULL) return;
    printTreeAsTree(root->right, depth + 1);
    for (int i = 0; i < depth; ++i) {
        printf("    ");
    }
    printf("%d\n", root->user.id);
    printTreeAsTree(root->left, depth + 1);
}