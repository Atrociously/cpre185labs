#include <stdio.h>

void how_many_whole_digits(int number);

int main(int argc, char *argv[]) {
    int input;

    printf("Pleas input an integer from 1 up to 10000000: ");
    scanf("%d", &input);

    if (input > 10000000 || input < 1) {
	printf("Invalid number!\n");
	return -1;
    }

    how_many_whole_digits(input);
    return 0;
}

void how_many_whole_digits(int number) {
    // for all if statements removed cast to double 
    if (number / 10000000 != 0) {
	printf("8 digits\n");
    } else if (number / 1000000 != 0) {
	printf("7 digits\n");
    } else if (number / 100000 != 0) {
	printf("6 digits\n");
    } else if (number / 10000 != 0) {
	printf("5 digits\n");
    } else if (number / 1000 != 0) {
	printf("4 digits\n");
    } else if (number / 100 != 0) {
	printf("3 digits\n");
    } else if (number / 10 != 0) {
	printf("2 digits\n");
    } else if (number / 1 != 0) {
	printf("1 digit\n");
    } 
}
