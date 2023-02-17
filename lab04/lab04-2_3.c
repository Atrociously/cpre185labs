#include <stdio.h>

void variable_swap(int i, int j);
void math_swap(int i, int j);

int main(int argc, char *argv[]) {
    int first = 0, second = 0;
    printf("Please input two integers separated by a space: ");
    //scanf("%lf %lf", &first, &second)
    scanf("%d %d", &first, &second); // fixed incorrect formatting
    
    printf("\n");
    variable_swap(first, second);
    printf("\n");
    math_swap(first, second);

    return 0;
}

void variable_swap(int i, int j) {
    printf("Now doing a swap using an extra variable: \n");
    printf("Before Swap: First: %d, Second: %d\n", i, j);

    int temp = i;
    i = j;
    j = temp;

    printf("After Swap: First %d, Second: %d\n", i, j);
}

void math_swap(int i, int j) {
    printf("Now doing a swap using addition and subtraction: \n");
    printf("Before Swap: First %d, Second: %d\n", i, j);

    i = i + j;
    j = i - j;
    i = i - j;

    printf("After Swap: First: %d, Second: %d\n", i, j);
}
