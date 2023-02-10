/*----------------------------------------------------------------------------
-		    SE 185: Lab 03 - Introduction to the DS4 and Functions	    	 -
-	Name:																	 -
- 	Section:																 -
-	NetID:																     -
-	Date:																	 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
int buttonsPressed(int a, int b, int c, int d);

/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc lab03-2.c -o lab03-2
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -b | ./lab03-2

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

    while (1)
    {
	    int triangle, circle, cross, square = 0;
	    scanf("%d,%d,%d,%d", &triangle, &circle, &cross, &square);

	    printf("%d", buttonsPressed(triangle, circle, cross, square));
	    fflush(stdout);
    }

    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */
int buttonsPressed(int a, int b, int c, int d) {
	return a + b + c + d;
}
