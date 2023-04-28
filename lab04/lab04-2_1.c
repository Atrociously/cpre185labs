#include <stdio.h>

int is_odd(int number);
int is_even(int number);

int main(int argc, char *argv[]) {
    int input = 0;

    printf("Please input an integer: ");
    scanf("%d", &input);

    //if (is_odd(input) = 1) {
    if (is_odd(input)) { // fixed incorrect if statement assignment and pointless comparison
	printf("%d is an odd nuber!\n", input);
    }
    //if (is_even(input) = 1) {
    if (is_even(input)) { // fixed incorrect if statement assignment and pointless comparison
	printf("%d is an even number!\n", input);
    }

    return 0;
}

int is_even(int number) {
    return !(number % 2);
}

int is_odd(int number) {
    return number % 2;
}
