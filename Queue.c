//
// Created by Ilya Atmazhitov on 24.08.2024.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initQueue(Queue* q) {
    q->head = NULL;
    q->size = 0;
}

void clearQueue(Queue* q) {
    while (q->head != NULL) {
        Node* next = q->head->next;
        free(q->head->item);
        free(q->head);
        q->head = next;
    }
    q->size = 0;
}

bool isEmpty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, const char* value) {
    Node* node = malloc(sizeof(Node));
    node->item = strdup(value);
    node->next = NULL;

    if (q->size == 0) {
        q->head = node;
    } else {
        Node* trav = q->head;
        while (trav->next != NULL) {
            trav = trav->next;
        }
        trav->next = node;
    }
    q->size++;
}

char* peeking(Queue* q) {
    if (q->size == 0) {
        fprintf(stderr, "Queue is Empty!\n");
        exit(1);
    }
    return q->head->item;
}

bool contains(Queue* q, const char* item) {
    if (q->size == 0) {
        fprintf(stderr, "Queue is Empty!\n");
        exit(1);
    }

    Node* trav = q->head;
    while (trav != NULL) {
        if (strcmp(trav->item, item) == 0) {
            return true;
        }
        trav = trav->next;
    }

    return false;
}

void removal(Queue* q, const char* item) {
    if (q->size == 0) {
        fprintf(stderr, "Queue is Empty!\n");
        exit(1);
    }

    if (strcmp(q->head->item, item) == 0) {
        Node* oldHead = q->head;
        q->head = q->head->next;
        free(oldHead->item);
        free(oldHead);
        q->size--;
        return;
    }

    Node* trav = q->head;
    while (trav->next != NULL) {
        if (strcmp(trav->next->item, item) == 0) {
            Node* delNode = trav->next;
            trav->next = delNode->next;
            free(delNode->item);
            free(delNode);
            q->size--;
            return;
        }
        trav = trav->next;
    }
}

void dequeue(Queue* queue) {
    if (isEmpty(queue)) return;

    Node* temp = queue->head;
    queue->head = queue->head->next;
    free(temp->item);
    free(temp);
    queue->size--;
}

void printQueue(Queue* q) {
    if (q->size > 0) {
        Node* trav = q->head;
        printf("{%s", trav->item);
        trav = trav->next;
        while(trav != NULL) {
            printf(" -> %s", trav->item);
            trav = trav->next;
        }
        printf("}\n");
    } else {
        printf("{}\n");
    }
}
