/*----------------------------------------------------------------------------
-		        SE 185: Lab 02 - Solving Simple Problems in C	    	 	 -
-	Name:																	 -
- 	Section:																 -
-	NetID:																     -
-	Date:																	 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int integer_result;
    double decimal_result;

    integer_result = 77 / 5;
    // This was bad because if formatted an int as a double
    //printf("The value of 77/5 is %lf, using integer math.\n", integer_result);
    printf("The value of 77/5 is %d, using integer math.\n", integer_result);

    integer_result = 2 + 3;
    // This was bad because it never gave the printf an input for the format specifier
    //printf("The value of 2+3 is %d.\n");
    printf("The value of 2+3 is %d.\n", integer_result);

    decimal_result = 1.0 / 22.0;
    // This was bad because it was formatting a double as an int
    //printf("The value 1.0/22.0 is %d.\n", decimal_result);
    printf("The value of 1.0/22.0 is %lf.\n", decimal_result);

    return 0;
}
