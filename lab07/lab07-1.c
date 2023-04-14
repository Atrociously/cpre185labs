/*---------------------------------------------------------------------------
-					  SE 185: Lab 07 - Pointers, Pointers and More Pointers -
-	Name: Jack Morrison                                                     -
-   Section: 3                                                              -
-	NetID: jackmorr                                                         -
-	Date: 03/24/2023                                                        -
-                                                                           -
-   This file provides the outline for your program.                        -
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									                                   -
-----------------------------------------------------------------------------*/
#include <stdio.h>

/* add whatever you see fit and need */

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/

/* put your function prototypes here */

/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/

// compile with gcc -o lab07-1 lab07-1.c

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int val = 42;
    int* point = &val;

    printf("%d\n", *point); // dereference the pointer and print the value stored in the memory address
    printf("%x\n", point);  // print the value of the pointer which is the memory address that the pointer points to
    printf("%x\n", &point); // create a reference to the pointer and print it's value which is the memory address the original pointer is store in

    return 0;

}

/*-----------------------------------------------------------------------------
-								Functions
-----------------------------------------------------------------------------*/

/* put your functions here */
