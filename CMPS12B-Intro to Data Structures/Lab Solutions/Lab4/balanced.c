/*Derrick DeBose Lab 4
 This programs reads input from a text file and then based on each line of input file we need to determine Yes or No if the braces in the input are balanced or not. If they are balenced like, ([{}]) print 'Y'. If they are not balanced like, [}{] print 'N'. We print out our output into a text file based on the each which line we are on in the input file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 80

struct Stack{//this is used to store the values of our stack
    int top;//top will be intialized to -1 and will be incremented before something is pushed onto the stack
    char array[ARRAY_SIZE];//the array of chars that holds strictly open braces
}st;//used to get to this data structure
//methods i will be using in my code
int isEmpty();
void push(char c);
void pop();
char peek();


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
    char c[ARRAY_SIZE];//intailize an array that can be used take in the text input
    while(fgets(c, ARRAY_SIZE, infile)) {//reads in text input until new line
        int pushCounter=0;//counters used to check to see if the braces are balenced
        int popCounter=0;
        int badPopCount=0;
        st.top=-1;//every time we get to a new line reset the stack.
        int length = strlen(c);//used for going through the for loop to check every char
        for(int i=0;i<length; i++) {//for to go through the char c[] array
            char currChar = c[i];//used for comparing ascii vaues
            if(currChar == '(') {//compare the ascii values of the place we are in the loop and an open brace
                pushCounter++;//add to Counter
                push(currChar);//all open braces just get pushed into the stack
            }else if(currChar == '{') {
                pushCounter++;
                push(currChar);
            }else if(currChar == '[') {
                pushCounter++;
                push(currChar);
            }else if(currChar == '<') {
                pushCounter++;
                push(currChar);
            }else if(currChar == ')'){//checks to see if we can pop off the open brace if there is one on the top of the stack
                if(isEmpty()){//checks to see if the stack is empty
                    badPopCount++;//if it is empty add one to badPopCount
                }else if(peek() != '('){//if the char on the stack is not the same open brace as the one passed in
                    badPopCount++;//increment bad count
                }else{//we had the correct open brace
                    popCounter++;//increase pop counter
                    pop();//pop off the top of the stack
                }
            }else if(currChar == '}'){
                if(isEmpty()){
                    badPopCount++;
                }else if(peek() != '{'){
                    badPopCount++;
                    
                }else{
                    popCounter++;
                    pop();
                }
            }else if(currChar == ']'){
                if(isEmpty()){
                    badPopCount++;
                }else if(peek() != '['){
                    badPopCount++;
                }else{
                    popCounter++;
                    pop();
                }
            }else if(currChar == '>'){
                if(isEmpty()){
                    badPopCount++;
                }else if(peek() != '<'){
                    badPopCount++;
                    
                }else{
                    popCounter++;
                    pop();
                }
            }
        }
        if(badPopCount == 0 && isEmpty() && pushCounter==popCounter ) {//if badPopCount never got changed incremented and the stack is Empty, and push and pop happen the same amount of times
            fprintf(outfile, "Y\n");//print out Y
        }else {
            fprintf(outfile, "N\n");//if badPopCount got incremented or the stack is not Empty, or push and pop did not happen the same amount of times, print out N

        }
    }

    fclose(infile);//closes the files we are using
    fclose(outfile);
    return EXIT_SUCCESS;
}
void push(char c){//method used to push things onto the stack
    if(st.top == ARRAY_SIZE-1){//if the stack is full
        return;//return
    }
    ++st.top;//increment top first
    st.array[st.top] = c;//then sent the new top to be the char passed in
}
int isEmpty(){//checks to see if the stack is empty or not
    if(st.top==-1)//if the top is -1 meaning it is empty, return true
        return 1;
    else//else reutrn false
        return 0;
}
void pop(){//pops off the top of the stack
    if(st.top==-1){//we cant pop if the stack is empty
        return;
    }
    st.top--;//decrement stack to get rid of the top of the stack
}
char peek (){//peek is used to see whats at the top of the stack
    return (st.array[st.top]);//returns a char of the top of the stack
}
