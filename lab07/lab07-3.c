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
int getRemaining(int factor, int inputPennies, int* remaining) {
    *remaining = inputPennies % factor;
    return (inputPennies / factor);
}

void makeChange(
    int price,
    int paid,
    int* changeDollars,
    int* changeQuarters,
    int* changeDimes,
    int* changeNickels,
    int* changePennies
) {
    int difference = paid - price;
    int remainder;

    *changeDollars = getRemaining(100, difference, &remainder);
    *changeQuarters = getRemaining(25, remainder, &remainder);
    *changeDimes = getRemaining(10, remainder, &remainder);
    *changeNickels = getRemaining(5, remainder, &remainder);
    *changePennies = remainder;
}

/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/

// compile with gcc -o lab07-1 lab07-1.c

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int price, paid;
    printf("Enter price in pennies: ");
    scanf("%d", &price);
    printf("Enter amount paid in pennies: ");
    scanf("%d", &paid);

    if (price < 0 || paid < 0) {
        printf("Price or Paid amount cannot be negative!");
        return -1;
    }
    while (price > paid) {
        int addon;
        printf("You must pay more!\nEnter more money to pay: ");
        scanf("%d", &addon);
        paid += addon;
    }

    int dollars, quarters, dimes, nickels, pennies = 0;
    makeChange(price, paid, &dollars, &quarters, &dimes, &nickels, &pennies);
    printf("Here is your change:\n");
    printf("Dollars: %d\n", dollars);
    printf("Quarters: %d\n", quarters);
    printf("Dimes: %d\n", dimes);
    printf("Nickels: %d\n", nickels);
    printf("Pennies: %d\n", pennies);

    return 0;
}

/*-----------------------------------------------------------------------------
-								Functions
-----------------------------------------------------------------------------*/

/* put your functions here */
