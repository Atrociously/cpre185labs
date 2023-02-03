/*----------------------------------------------------------------------------
-		        SE 185: Lab 02 - Solving Simple Problems in C	    	 	 -
-	Name: Jack Morrison														 -
- 	Section: 3																 -
-	NetID: jackmorr																     -
-	Date: 02/03/2023																	 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int x, y, z;
    printf("Enter a width: ");
    scanf("%d", &x);
    printf("Enter a height: ");
    scanf("%d", &y);
    printf("Enter a depth: ");
    scanf("%d", &z);

    printf("A %d by %d by %d rectangular prism's volume is %d\n", x, y, z, x * y * z);
    return 0;
}
