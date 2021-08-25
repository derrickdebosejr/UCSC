#include "queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>



Node* newNode(int x){//method to create a node
    Node* n = malloc(sizeof(Node));//allocate memory for the node
    if( n == NULL ){//if statement equivalent to the assert function
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    n->item = x;//item stored in the node is the one passed in
    n->next = NULL;//newest node so next is null
    return n;//return the node
}

Queue* newQueue(){//method to create a queue
    Queue* que = malloc(sizeof(Queue));//allocate memory for the queue
    if( que == NULL ){//if statement equivalent to the assert function
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    // initialize the fields of the queue structure return que
    que->head = NULL;
    que->tail = NULL;
    return que;
}

void freeQueue(Queue* que){//free up the allocated memory for the nodes and queue;
    if( que == NULL ){//checks if the que is null
        fprintf(stderr, "free failed\n");//failure message
        exit(EXIT_FAILURE);
    }else{
        Node* currNode;//reference to a node
        currNode = que->head;//references the head
        while(isEmpty(que)==0){//while the queue is not empty
            dequeueNoFile(que);//dequeue and free node
        }
        free(que->head);//free head and tail
        free(que->tail);
        que->head = NULL;//set head and tail to null
        que->tail = NULL;
        free(que);//free queue
        que = NULL;//set queue to null
    }
    return;
    
}

int isEmpty(Queue* que){//A check to see if the queue is empty
    if(que->head == NULL){
        return 1;
    }
    return 0;
}

void printQueue(FILE* out, Queue* que){//function to print out the queue
    Node* curr;//pointer to a node
    if(isEmpty(que)){//if the queue is empty
        fprintf(out, "Queue is empty\n");//print statement
    }else{
        curr = que->head;//curr points to head
        fprintf(out, "Queue is ");//starting message
        while(curr != NULL){//goes through the queue
            fprintf(out, "%d ", curr->item);//print out each number with a space after
            curr = curr->next;//tranverses through queue
        }
        fprintf(out,"\n");//new line after all the numbers are printed
    }
}

void enqueue(Queue* que, int item, FILE* out){//adds nodes to the queue
    Node* N = newNode(item);//create a new node
    if(isEmpty(que)){//if the queue is empty
        que->head=N;//head and tail are the same
        que->tail=N;
    }else{
        que->tail->next=N;//add node to end of the list
        que->tail = N;//set tail to new node
    }
   
    fprintf(out, "Enqueue %d\n", item);//print
}
int dequeueNoFile(Queue* que){//for the free method to dequeue all
    Node* temp;//reference to node
    if(isEmpty(que)){//if the list is empty
        return 0;//return nothing to dequeue
    }else{
        temp = que->head;//temp points to queue head
        que->head= que->head->next;//move head forward
        return temp->item;//return the number dequeued
    }
    free(&temp);//free the node that was dequeued
    temp = NULL;//set to null
}
int dequeue(FILE* out, Queue* que){
    Node* temp;//reference to node
    if(isEmpty(que)){//if the list is empty
        fprintf(out, "Dequeue fails\n");//print
        return 0;//return nothing to dequeue
    }else{
        temp = que->head;//temp points to queue head
        que->head= que->head->next;//move head forward
        fprintf(out, "Dequeue %d\n", temp->item);//print
        return temp->item;//return the number dequeued
    }
    free(&temp);//free the node that was dequeued
    temp = NULL;//set to null
}

