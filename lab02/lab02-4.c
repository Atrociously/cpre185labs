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
    int a = 6427 + 1725;
    int b = (6971 + 3925) - 95;
    double c = 79 + 12 / 5; // does integer division then turns it into a double losing the decimal
    double d = 3640.0 / 107.9;
    int e = (22 / 3) * 3;
    int f = 22 / (3 * 3);
    double g = 22 / (3 * 3); // does integer division then turns it into a double losing the decimal
    double h = 22 / 3 * 3; // does integer division then turns it into a double losing the decimal
    double i = (22.0 / 3) * 3.0;
    int j = 22.0 / (3 * 3.0);
    double k = 22.0 / 3.0 * 3.0;

    printf("a: %d\nb: %d\nc: %.2lf\nd: %.2lf\ne: %d\nf: %d\ng: %.2lf\nh: %.2lf\ni: %.2lf\nj: %d\nk: %.2lf\n", a, b, c, d, e, f, g, h, i, j, k);

    double radius = 23.517 / 2 / M_PI;
    double l = M_PI * pow(radius, 2);
    double m = 14.0 * 0.3048;
    double n = (76.0 - 32.0) / 1.8;

    printf("l: %.2lf\nm: %.2lf\nn: %.2lf", l, m, n);
    return 0;
}
