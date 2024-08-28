//
// Created by Ilya Atmazhitov on 24.08.2024.
//

#ifndef BINARYTREE_QUEUE_H
#define BINARYTREE_QUEUE_H

#include <stdbool.h>

typedef struct Node {
    char* item;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} Queue;

void initQueue(Queue* q);
void clearQueue(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, const char* value);
char* peeking(Queue* q);
bool contains(Queue* q, const char* item);
void removal(Queue* q, const char* item);
void dequeue(Queue* q);
void printQueue(Queue* q);


#endif //BINARYTREE_QUEUE_H
