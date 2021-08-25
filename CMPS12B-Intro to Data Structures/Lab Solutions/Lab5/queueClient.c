#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

int main(int argc, char* argv[]) {
    
    FILE* infile;//used to read in the arguments as files
    FILE* outfile;
    if(argc != 3){//checks to see if we are using an input and output file
        printf("Usage: %s some-string\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    infile = fopen(argv[1],"r");//intializes the first argument passed in that needs to be read in
    if(infile == NULL) {//checks to see if there actually is a file with that name
        fprintf(stderr, "ERROR: couldn't open %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    outfile = fopen(argv[2],"w");//intializes the secind argument passed in that needs to be written into
    if(outfile == NULL) {//checks to see if there actually is a file with that name
        fprintf(stderr, "ERROR: couldn't open %s for writing\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    char c[100];//array for the input line
    const char s[2] = " ";//the character to split
    char* token;//token of part of the input line
    int insert;//used to enqueue
    Queue* queue = newQueue();//create a queue
    while(fgets(c, 100, infile)) {//read input until a new line character
        int length =strlen(c);//the length of the string
        for(int i=0;i<length; i++) {//for to go through the char c[] array
            char currChar = c[i];//used for comparing ascii vaues
            if(currChar == 'E') {//compare the ascii values of the place we are in the loop and E
                token = strtok(c,s);//token of the letter E
                token = strtok(NULL, s);// token of the number
                insert = atoi(token);//convert a char array to an int
                enqueue(queue,insert,outfile);//enqueue the number read in to the queue
            }
            if(currChar == 'D'){//compare the ascii values of the place we are in the loop and D
                dequeue(outfile,queue);//dequeue the queue
            }
            if(currChar == 'P'){//compare the ascii values of the place we are in the loop and P
                printQueue(outfile,queue);//print out the queue
            }
        }
    }
    freeQueue(queue);//free the allocated memory from the queue
    fclose(infile);//closes the files we are using
    fclose(outfile);
    return EXIT_SUCCESS;
}
