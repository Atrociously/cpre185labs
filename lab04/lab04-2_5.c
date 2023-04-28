#include <stdio.h>

int is_positive(int number);
int is_negative(int number);
int is_zero(int number);

int main(int argc, char *argv[]) {
    int number;

    printf("Please type a number between -10000 and 10000: ");
    scanf("%d", &number);

    if (number > 10000 || number < -10000) {
	printf("Number is out of range!\n");
	return -1;
    }
    //if ((is_positive(number) & !is_negative(number)) | is_zero(number)) {
    if ((is_positive(number) && !is_negative(number)) || is_zero(number)) { // fixed incorrect logic statements
	printf("%d is a whole number.\n", number);
    } else {
	printf("%d is a non-whole number.\n", number);
    }

    return 0;
}

int is_positive(int number) {
    if (number > 0) {
	printf("%d is positive and ", number);
	return 1;
    }
    printf("%d is non-positive and ", number);
    return 0;
}

int is_negative(int number) {
    if (number < 0) {
	printf("%d is negative and ", number);
	return 1;
    }
    printf("%d is non-negative and ", number);
    return 0;
}

int is_zero(int number) {
    //if (number = 0) {
    if (number == 0) { // fixed incorrect if expression assignment
	//printf("%d is zero and ", n);
	printf("%d is zero and ", number); // fixed incorrect variable name
	return 1;
    }
    printf("%d is non-zero and ", number);
    return 0;
}
