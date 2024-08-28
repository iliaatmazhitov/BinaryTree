//
// Created by Ilya Atmazhitov on 24.08.2024.
//

#ifndef BINARYTREE_BST_H
#define BINARYTREE_BST_H

#include "Queue.h"

typedef struct NodeBST {
    char* key;
    Queue* field;
    struct NodeBST* right;
    struct NodeBST* left;
};


struct NodeBST* initNode(char* value);
bool checkDuplicate(struct NodeBST* node, char* key);
struct NodeBST* insertNode(struct NodeBST* node, char* key, char* item);
void printTree(struct NodeBST* root, int level);
void generateDotFile(struct NodeBST* root, FILE *file);
void visualizeTree(struct NodeBST* root, const char* filename);
void loadTreeFromFile(struct NodeBST** root, const char* filename);
struct NodeBST* minValueNode(struct NodeBST* node);
struct NodeBST* deleteNode(struct NodeBST* root, char* key);
void traverseTree(struct NodeBST* root, const char* prefix);
void searchByKey(struct NodeBST* root, const char* key, struct NodeBST** result, int* count);
struct NodeBST** findByKey(struct NodeBST* root, const char* key, int* count);
void searchAndPrintResults(struct NodeBST* node, const char* searchKey);
void findAllGreaterThan(struct NodeBST* root, const char* key, struct NodeBST** result, int* count);
struct NodeBST** findSmallestGreaterThan(struct NodeBST* root, const char* key, int* count);
void printLargerElements(struct NodeBST* root, const char * key);
void searchAndPrintSmallestGreaterThan(struct NodeBST* root, const char* key);
void deleteTree(struct NodeBST** node);
void delTree(struct NodeBST* node);
int D_Timing();




#endif //BINARYTREE_BST_H
