/*
 CREATED: Derrick DeBose April 27, 2018
 CHANGED: May 2, 2018
 
This is the main code that tests the Apint ADT. It makes apints and uses them to print, add, subtract, and multiply
 
*/

#include "apint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void){
    //strings a-f i will be using to convert into apints
    char a[100]={"+23875903272098752"};
    char b[100]={"-513123412341235451345325431241235"};
    char c[100]={'0','1','2','3','4','5','6','7','8','9','\0'};
    char d[100]={"41541123961"};
    char e[100]={"997878676585877869"};
    char f[100]={"66567676858777656786765"};
    
    
    //int that will be converted to an apint
    int i = -238527;
    int j = 400;
    int k = 20;
    
    //pointers to apint structs
    apint myApint1, myApint2, myApint3, myApint4, myApint5, myApint6, myApint7, myApint8, myApint9,
    myApint10, myApint11, myApint12, myApint13, myApint14, myApint15, myApint16, myApint17;
    
    //a default constructor to allocate memory for Apints
    newApint(&myApint1);
    newApint(&myApint2);
    newApint(&myApint3);
    newApint(&myApint4);
    newApint(&myApint5);
    newApint(&myApint6);
    newApint(&myApint7);
    newApint(&myApint8);
    newApint(&myApint9);
    newApint(&myApint10);
    newApint(&myApint11);
    newApint(&myApint12);
    newApint(&myApint13);
    newApint(&myApint14);
    newApint(&myApint15);
    newApint(&myApint16);
    newApint(&myApint17);
    
    
    //creates an apint from a string
    newApintStr(&myApint1, a);
    newApintStr(&myApint2, b);
    newApintStr(&myApint3, c);
    newApintStr(&myApint4, d);
    newApintStr(&myApint5, e);
    newApintStr(&myApint6, f);
    
    //creates an apint from an int
    newApintInt(&myApint10,i);
    newApintInt(&myApint12,j);
    newApintInt(&myApint13,k);
    
    //Add method takes the sum of first 2 Apint arguments and stores the sum in the 3rd one
    add(myApint5,myApint6,myApint7);
    
    //Subtract method takes the difference of first 2 Apint arguments and stores the difference in the 3rd one
    subtract(myApint3,myApint4,myApint8);
    
    //Multiply method takes the difference of first 2 Apint arguments
    //and an empty Apint 3rd one, and stores the product in the 4th argument
    multiply(myApint1,myApint2,myApint11, myApint9);
    
    //Add method takes the sum of first 2 Apint arguments and stores the sum in the 3rd one
    add(myApint12,myApint13,myApint14);
    
    //Multiply method takes the difference of first 2 Apint arguments
    //and an empty Apint 3rd one, and stores the product in the 4th argument
    multiply(myApint12,myApint13,myApint17, myApint16);
    
    //Subtract method takes the difference of first 2 Apint arguments and stores the difference in the 3rd one
    subtract(myApint12,myApint13,myApint15);
    
    
    //string of numbers to apint print statement
    printf("I will will be printing char a[] %s with a '+' in the front of the string and printing as an apint: ", a);
    print (myApint1);
    printf("I will will be printing char b[] %s with a '-' in the front of the string and printing as an apint: ", b);
    print (myApint2);
    
    //int to string print statement
    printf("I will will be printing int i with a %d and printing as an apint: ",i);
    print (myApint10);
    
    
    printf("I will be adding %d and %d and their sum is: ",j,k);
    print (myApint14);
    
    printf("I will be subtracting %d and %d and their difference is: ",j,k);
    print (myApint15);
    
    printf("I will be multiplying %d and %d and their product is: ",j,k);
    print (myApint16);
    
    //print sum
    printf("I will be adding %s and %s and their sum is: ",e,f);
    print (myApint7);
    
    //print difference
    printf("I will be subtracting %s and %s and their difference is: ",c,d);
    print (myApint8);
    
    //print product
    printf("I will be multiplying %s and %s and their product is: ",a,b);
    print (myApint9);
    
    //free up the allocated memory
    free(myApint1);
    free(myApint2);
    free(myApint3);
    free(myApint4);
    free(myApint5);
    free(myApint6);
    free(myApint7);
    free(myApint8);
    free(myApint9);
    free(myApint10);
    free(myApint11);
    free(myApint12);
    free(myApint13);
    free(myApint14);
    free(myApint15);
    free(myApint16);
    free(myApint17);
    
    
    return 0;
}
