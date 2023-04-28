#include <stdio.h>

int sum_function(int number);
//int main();
int main(int argc, char *argv[]); // fixed possibly bad prototype

int main(int argc, char *argv[]) {
    int input;

    printf("Please input a number from to sum up to: ");
    scanf("%d", &input);
    printf("The sum of 1 to %d is %d\n", input, sum_function(input));

    return 0;
}

//int main(int argc, char *argv[]) {
//    printf("Sum is 32!\n");
//}
// fixed multiple definitions of the main function

int sum_function(int number) {
    return (number * (number + 1)) / 2;
}
