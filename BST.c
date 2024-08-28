//
// Created by Ilya Atmazhitov on 24.08.2024.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BST.h"


//char* key;
//Queue* field;
//struct NodeBST* right;
//struct NodeBST* left;

struct NodeBST* initNode(char* value) {
    struct NodeBST* temp = (struct NodeBST*)malloc(sizeof(struct NodeBST));
    if (temp == NULL) {
        printf("Memeory Allocation Errored!");
        exit(1);
    }
    temp -> field = (Queue *)malloc(sizeof(Queue));
    initQueue(temp -> field);
    temp -> key = strdup(value);
    temp -> left = temp -> right = NULL;
    return temp;
}


bool checkDuplicate(struct NodeBST* node, char* key) {
    if (node == NULL) {
        return false;
    }

    if (strcmp(key, node -> key) == 0)
    {
        return true;
    }

    /* Otherwise, recur down the tree */
    if (strcmp(key, node -> key) < 0)
        return checkDuplicate(node->left, key);
    else
        return checkDuplicate(node->right, key);

}

struct NodeBST* minValueNode(struct NodeBST* node)
{
    struct NodeBST* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct NodeBST* insertNode(struct NodeBST* node, char* key, char* item) {
    if (node == NULL) {
        node = initNode(key);
        enqueue(node->field, key);
        return node;
    }

    int cmp = strcmp(key, node->key);
    if (cmp == 0) {
        enqueue(node->field, item ? item : "NULL");
    } else if (cmp < 0) {
        node->left = insertNode(node->left, key, item);
    } else {
        node->right = insertNode(node->right, key, item);
    }

    return node;
}

struct NodeBST* deleteNode(struct NodeBST* root, char* key) {
    if (root == NULL) return root;

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        root->left = deleteNode(root->left, key);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, key);
    } else {
        dequeue(root->field);

        if (isEmpty(root->field)) {
            if (root->left == NULL) {
                struct NodeBST* temp = root->right;
                free(root->key);
                clearQueue(root->field);
                free(root->field);
                free(root);
                return temp;
            } else if (root->right == NULL) {
                struct NodeBST* temp = root->left;
                free(root->key);
                clearQueue(root->field);
                free(root->field);
                free(root);
                return temp;
            }

            struct NodeBST* temp = minValueNode(root->right);
            free(root->key);
            root->key = strdup(temp->key);
            Queue* tempQueue = root->field;
            root->field = temp->field;
            temp->field = tempQueue;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    return root;
}


// Format output

void printTree(struct NodeBST* root, int level) {
    if (root == NULL) {
        return;
    }

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("   ");
    }
    printf("└── %s: ", root->key);
    printQueue(root->field);
    printf("\n");

    printTree(root->left, level + 1);
}
// Graph output

void generateDotFile(struct NodeBST* root, FILE *file) {
    if (root == NULL) return;

    fprintf(file, "    \"%s\" [label=\"%s: ", root->key, root->key);
    Node* current = root->field->head;
    while (current) {
        fprintf(file, "%s\\n", current->item);
        current = current->next;
    }
    fprintf(file, "\"];\n");

    if (root->left) {
        fprintf(file, "    \"%s\" -> \"%s\";\n", root->key, root->left->key);
        generateDotFile(root->left, file);
    }

    if (root->right) {
        fprintf(file, "    \"%s\" -> \"%s\";\n", root->key, root->right->key);
        generateDotFile(root->right, file);
    }
}

void visualizeTree(struct NodeBST* root, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }


    fprintf(file, "digraph BST {\n");
    fprintf(file, "    node [fontname=\"Arial\"];\n");

    generateDotFile(root, file);

    fprintf(file, "}\n");
    fclose(file);
    char command[256];
    sprintf(command, "dot -Tpng %s -o tree.png", filename);
    system(command);
}

void loadTreeFromFile(struct NodeBST** root, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    char key[256], item[256];
    while(fscanf(file, "%255s\n%255s\n", key, item) == 2) {
        *root = insertNode(*root, key, item);
    }

    fclose(file);
}

void traverseTree(struct NodeBST* root, const char* prefix) {
    if (root == NULL) return;

    if (!isEmpty(root->field) && strncmp(peeking(root->field), prefix, strlen(prefix)) == 0) {
        printf("%s: ", root->key);
        printQueue(root->field);
        printf("\n");
    }

    traverseTree(root->left, prefix);
    traverseTree(root->right, prefix);
}

void searchByKey(struct NodeBST* root, const char* key, struct NodeBST** result, int* count) {
    if (root == NULL) return;

    int cmp = strcmp(key, root->key);
    if (cmp == 0) {
        result[*count] = root;
        (*count)++;
    }

    if (cmp <= 0) searchByKey(root->left, key, result, count);
    if (cmp >= 0) searchByKey(root->right, key, result, count);
}

struct NodeBST** findByKey(struct NodeBST* root, const char* key, int* count) {
    struct NodeBST** result = malloc(sizeof(struct NodeBST*) * 100); // Предполагаем, что не более 100 совпадений
    *count = 0;
    searchByKey(root, key, result, count);
    return result;
}


void searchAndPrintResults(struct NodeBST* node, const char* searchKey) {
    int count;
    struct NodeBST** found = findByKey(node, searchKey, &count);

    printf("Found %d matches for key '%s':\n", count, searchKey);
    for (int i = 0; i < count; i++) {
        printf("Match %d:\n", i+1);
        printf("  Key: %s\n", found[i]->key);
        printf("  Queue contents: ");
        printQueue(found[i]->field);
        printf("\n");
    }

    free(found);
}


void findAllGreaterThan(struct NodeBST* root, const char* key, struct NodeBST** result, int* count) {
    if (root == NULL) return;

    findAllGreaterThan(root->left, key, result, count);

    if (strcmp(root->key, key) > 0) {
        result[*count] = root;
        (*count)++;
    }

    findAllGreaterThan(root->right, key, result, count);
}

struct NodeBST** findSmallestGreaterThan(struct NodeBST* root, const char* key, int* count) {
    struct NodeBST** result = malloc(sizeof(struct NodeBST*) * 100); // Предполагаем, что не более 100 совпадений
    *count = 0;
    findAllGreaterThan(root, key, result, count);
    return result;
}

void searchAndPrintSmallestGreaterThan(struct NodeBST* root, const char* key) {
    int count;
    struct NodeBST** result = findSmallestGreaterThan(root, key, &count);

    if (count == 0) {
        printf("No keys found that are greater than '%s'\n", key);
    } else {
        printf("Keys greater than '%s' (in ascending order):\n", key);
        for (int i = 0; i < count; i++) {
            printf("Match %d:\n", i+1);
            printf("  Key: %s\n", result[i]->key);
            printf("  Queue contents: ");
            printQueue(result[i]->field);
            printf("\n");
        }
    }

    free(result);
}

void deleteTree(struct NodeBST** node) {
    if (*node == NULL) return;

    deleteTree(&((*node)->left));
    deleteTree(&((*node)->right));

    free((*node)->key);
    clearQueue((*node)->field);
    free((*node)->field);
    free(*node);

    *node = NULL;
}

void delTree(struct NodeBST* node) {
    if (node == NULL) return;

    delTree(node->left);
    delTree(node->right);
    free(node->key);
    clearQueue(node->field);
    free(node->field);
    free(node);
}

int D_Timing() {
    struct NodeBST* root = NULL;
    int n = 10;
    int key[10000];
    int cnt = 1000000;
    clock_t start, end;
    srand(time(NULL));

    while (n-- > 0) {
        // Генерация случайных ключей для поиска
        for (int i = 0; i < 10000; ++i) {
            key[i] = rand() * rand();
        }

        // Вставка случайных ключей в дерево
        for (int i = 0; i < cnt; ) {
            int k = rand() * rand();
            char strKey[12]; // 11 символов достаточно для хранения 32-битного int, +1 для '\0'
            snprintf(strKey, sizeof(strKey), "%d", k);

            if (!checkDuplicate(root, strKey)) {
                root = insertNode(root, strKey, "item");
                ++i;
            }
        }

        // Поиск ключей в дереве и измерение времени
        int foundCount = 0;
        start = clock();
        for (int i = 0; i < 10000; ++i) {
            char strKey[12];
            snprintf(strKey, sizeof(strKey), "%d", key[i]);

            int count;
            struct NodeBST** found = findByKey(root, strKey, &count);
            if (count > 0) {
                foundCount++;
            }
            free(found);
        }
        end = clock();

        printf("%d items were found\n", foundCount);
        printf("Test #%d, number of nodes = %d, time = %.3f seconds\n", 10 - n, (10 - n) * cnt, (double)(end - start) / CLOCKS_PER_SEC);
    }

    // Удаление дерева
    deleteTree(&root);

    return 1;
}