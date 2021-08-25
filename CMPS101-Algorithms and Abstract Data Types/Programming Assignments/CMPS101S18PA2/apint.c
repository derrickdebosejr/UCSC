/*
 CREATED: Derrick DeBose April 27, 2018
 CHANGED: May 2, 2018
 
 apint.c is the file that is the apint ADT that creates apints
 from strings or ints and can manipulate the data with methods to add,
 subtract, and multiply the numbers. There is a method that can print out the apint to the system

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "apint.h"
#define MAXARRAY 100
#define TRUE 1
#define FALSE 0

/*
 This struct is the Arbitrary Precession Integer
 */
typedef struct newAPINTStruct{
    int *number;//array of ints to represent an apint
    int boolean;//negative flag
}newAPINTStruct;

/*
 Method accepts a pointer an apint struct and allocates memory for the apint
 */
void newApint(apint *a){// a pointer to the struct
    (*a)= calloc(1,sizeof(apint));//allocate memory for the apint pointer
    (*a)->number= calloc(MAXARRAY,sizeof(int));//allocate memory for the array
    for(int j=0;j<MAXARRAY;j++){
        (*a)->number[j]=0;//set the array to zero
    }
    
    (*a)->boolean = FALSE;//set the negative flag to false
}

/*
 Method accepts a pointer an apint struct and a string of characters that will be put into the apint structure
 */
void newApintStr(apint *api, char c[]) {//converts a string of ints to an apint
    int length = strlen(c);//length of the string
    for(int k=0;k<length-1;k++){
        if(c[k]=='-'){//check to see if the number is negative
            (*api)->boolean= TRUE;
            
        }
    }
    int counter = MAXARRAY-1;//start from the back of the int array
    for( int i=length-1;i>=0;i--){//start at the end of the string
        if(c[i]=='-'){//check for a negative sign
            (*api)->number[counter] =(c[i]-'-');
        }
        
        else if(c[i]=='+'){//check for a positive sign
            (*api)->number[counter] =(c[i]-'+');
        }
        
        else{//converts the char to a number and stores it in the array
            (*api)->number[counter] =(c[i]-'0');
        }
        
        counter--;
    }
}

/*
 Method accepts a pointer an apint struct and an int that will be put into the apint structure
 */
void newApintInt(apint *api, int a) {
    char c[MAXARRAY];//allocates memory for a string
    sprintf(c,"%d",a);//method converts an int to a string
    int length= strlen(c);
    for(int k=0;k<=MAXARRAY-1;k++){
        if(c[k]=='-'){//check to see if the number is negative
            (*api)->boolean= TRUE;
        }
    }
    int counter = MAXARRAY-1;
    for( int i=length-1;i>=0;i--){
        if(c[i]=='-'){//check for a negative sign
            (*api)->number[counter] =(c[i]-'-');
        }
        
        else if(c[i]=='+'){//check for a positive sign
            (*api)->number[counter] =(c[i]-'+');
        }
        
        else{//converts the char to a number and stores it in the array
            (*api)->number[counter] =(c[i]-'0');
            
        }
        counter--;
    }
}

/*
The print method checks if the apint passed in is
zero and will print out zero otherwise prints out the number and removes all the leading zeros in the apint.
*/
void print(apint a){//method used to print out an apint
    if(a->boolean == TRUE){//if the number is negative
        printf("-");
    }
    int counter =0;
    while(a->number[counter]==0){//checks ends when has passed all the leading zeros
        counter++;
        if(counter == MAXARRAY){//if made it to the max array then there is a 0 stored
            printf("0");
        }
    }
    for(int i=0+counter;i<MAXARRAY; i++){//starts from counter to maxarray
        printf("%d", a->number[i]);;//add number to the back of string
    }
    printf("\n\n");
}

/*The add method in my code starts at the back of the list we add the 2 ints
 and then calculate carry based on the sum. The result stores the sum.
 The arguments are a+b=result
*/
void add(apint a, apint b, apint result){//adds 2 apints and store the sum in result
    int carry =0;//used to determine what needs to be carried
    int total =0;//used as a temp to determine int needs to be stored in the array
    for(int i=MAXARRAY-1;i>=0;i--){//start at the back of the list to add
        total = (a->number[i])+(b->number[i])+carry;//total is the addition of the 2 numbers including the carry
        (result->number[i])=total%10;//if total is  15 or 25, result=5
        total=total/10;//if total is 15 or 25, total 1,2
        carry= total;
    }
}

/*
 The subtract method in my code first determines which number is bigger in size.
 If the second number is larger than the first then we will subtract the second number from the first
 and set the difference to negative. We subtract a-b when a>b and b-a when b>a.
 The difference is a-b = result
*/
void subtract(apint a, apint b, apint result){
    int carry =0;
    for(int i=0;i<=MAXARRAY-1;i++){//loop to determine which number is larger
        if((a->number[i])>(b->number[i])){//if a is bigger in size
            result->boolean=FALSE;//then difference must not be negative
            for(int j = MAXARRAY-1;j >= 0;j--){//start from the back of the array
                if((a->number[j]+carry)>=(b->number[j])){//we can just subtract if the top item is larger
                    (result->number[j])=a->number[j]-(b->number[j])+carry;//subtract and include the carry
                    carry =0;//carry must be 0
                }
                else{//if i need to carry and b is bigger than a
                    a->number[j]=a->number[j]+10;//add 10 to the top function is equivalent to carrying
                    result->number[j]=a->number[j]-b->number[j]+carry;//then you may subtract
                    carry = -1;//carry a -1 if need to be carried
                    
                }
            }
            break;//escape the i for loop
        }
        if((b->number[i])>(a->number[i])){//if b is bigger in size
            result->boolean = TRUE;//then difference must be negative
            for(int j = MAXARRAY-1;j >= 0;j--){//start from the back of the array
                if((b->number[j]+carry)>=a->number[j]){//subtract the bigger number by smaller one and set to negative
                    result->number[j]=b->number[j]-a->number[j]+carry;//subtract and include the carry
                    carry =0;//carry must be 0
                }
                else{//if i need to carry and a is bigger than b
                    b->number[j]=b->number[j]+10;//add 10 to the larger function is equivalent to carrying
                    result->number[j]=b->number[j]-a->number[j]+carry;//then you may subtract
                    carry = -1;//carry a -1 if need to be carried
                    
                }
            }
            break;//escape the i for loop
        }
    
    }
}

/*
The shift method to shift the data in order for there to be zeros at the end to hold multiplication process.
Method used in the multiply function to add b zeros to the end of the apint.
*/
apint shift(apint a, int b){
    apint total;//a temp int to transfer the data
    newApint(&total);
    for(int i=MAXARRAY-1;i>=0+b;i--){
        total->number[i-b]=a->number[i];//more the data b spaces to the left
    }
    return total;
}

/*
The multiply method first determines which number is bigger in size.
Total is calculated by multiplying the 2 apints and adding by the carry at that index then uses a shift method
to shift the data in order for there to be zeros at the end to hold the long multiplication process.
The arguments passed in are a x b = result and the total apint is an
empty apint that is used to be passed into the shift method
*/
void multiply(apint a, apint b, apint total, apint result){
    int carry=0;
    if(a->boolean==b->boolean){//test to figure out if product is negative or not
        result->boolean=FALSE;
    }else{
        result->boolean = TRUE;
    }
    for(int i=0;i<=MAXARRAY-1;i++){//loop to figure out which operation goes on top and which goes on the bottom
        if((a->number[i])>(b->number[i])){//if the first apint element is larger
            for(int j=MAXARRAY-1;j>=0;j--){
                carry=0;
                for(int k=MAXARRAY-1;k>=0;k--){
                    (total->number[k])=(a->number[k])*(b->number[j])+carry;//multipy a and b and add carry
                    carry = (total->number[k])/10;//carry is total over 10 for example if total is 54 then carry is 5
                    (total->number[k])= (total->number[k])%10;//mod by 10 to get rid of the higher order terms
                }
                total = shift(total,MAXARRAY-1-j);//method to know how much to shift data to the left
                add(total,result,result);//add the total of the mulitpy and n is the running total of the whole process
            }
            break;
        }
        if((b->number[i])>(a->number[i])){//if the second apint element is larger
            for(int j=MAXARRAY-1;j>=0;j--){
                carry=0;
                for(int k=MAXARRAY-1;k>=0;k--){
                    (total->number[k])=(a->number[k]*b->number[j]+carry);//multipy a and b and add carry
                    carry = (total->number[k])/10;//carry is total over 10 for example if total is 54 then carry is 5
                    (total->number[k])= (total->number[k])%10;//mod by 10 to get rid of the higher order terms
                }
                total =shift(total,MAXARRAY-1-j);//method to know how much to shift data to the left
                add(total,result,result);//add the total of the mulitpy and n is the running total of the whole process
            }
            break;
        }
    }
}



