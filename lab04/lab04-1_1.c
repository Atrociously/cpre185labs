#include <stdio.h>

int main(int argc, char *argv[]) {
    int i, j;

    //printf("Enter an integer: ")
    printf("Enter an integer: "); // fixed missing semicolon
    scanf("%d", &i);

    printf("Enter another integer: ");
    //scanf("%d", &j)
    scanf("%d", &j);  // fixed missing semicolon

    if (j % i == 0) {
	printf("%d divides %d\n", i, j);
    //} else 
    } else { // fixed missing brace
	// pritf("%d does not divide %d\n", i, j);
	printf("%d does not divide %d\n", i, j); // fixed misspelling of printf
	printf("%d %% %d is %d\n", j, i, (j % i));
    }

    return 0;
}
