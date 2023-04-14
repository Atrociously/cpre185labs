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
#include <stdlib.h>

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

    /* implement your solutions here */
    char* userName = malloc(sizeof(char) * 1024);
    char* userMajor = malloc(sizeof(char) * 1024);

    printf("Enter name: ");
    scanf(" %[^\n]", userName);
    printf("Enter major: ");
    scanf(" %[^\n]", userMajor);

    printf("Name: %s Major: %s", userName, userMajor);

    free(userName);
    free(userMajor);
    return 0;
}

/*-----------------------------------------------------------------------------
-								Functions
-----------------------------------------------------------------------------*/

/* put your functions here */
