#ifndef _QUEUE_
#define _QUEUE_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct NodeObj{//node struct
    int item;//int that will be stored in the node
    struct NodeObj* next;//pointer to the next node
}Node;

typedef struct {//queue struct
    Node* head;//reference to front
    Node* tail;//reference to end
}Queue;

//creates nodes and queue
Node* newNode(int x);
Queue* newQueue();
//prototypes
void freeQueue(Queue* que);
int isEmpty(Queue* que);
void printQueue(FILE* out, Queue* que);
void enqueue(Queue* que, int item, FILE* out);
int dequeueNoFile(Queue* que);
int dequeue(FILE* out, Queue* que);


#endif
