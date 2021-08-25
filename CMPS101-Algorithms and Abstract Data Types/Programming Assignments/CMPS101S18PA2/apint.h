/*CREATED: Derrick DeBose April 27, 2018
 CHANGED: May 2, 2018
 
 apint.h is the header file to apint.c and has the prototypes to the apint.c methods
 
 */

#ifndef _apint_
#define _apint_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//the structure for the apint ADT
typedef struct newAPINTStruct *apint;//stores pointers to an array of int and to an int

//creation methods
void newApint(apint *a);// a pointer to the struct
void newApintStr(apint *apI, char c[]);//converts a string of ints to an apint
void newApintInt(apint *apI, int a);//method accepts an int and converts it to an apint

//Manipulation methods
void print(apint a);//method used to print out an apint
void add(apint a, apint b, apint result);//adds 2 apints and store the sum in result
void subtract(apint a, apint b, apint result);//subracts 2 apints and store the differnce in result
apint shift(apint a,int b);//method used in the multiply function to add b zeros to the end of the apint
void multiply(apint a, apint b,apint total, apint result);//method used to multiply a and b and store the product in result and the total argument is used as an apint to pass into the shift method


#endif
