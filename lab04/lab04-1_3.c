#include <time.h>
#include <stdio.h> // fixed missing include
#include <stdlib.h> // fixed missing include

void hoo();
void print_face(int selection); // fixed missing function definition

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int selection = 0;

    printf("Enter 1 for happy, 2 for sad, 3 for neutral, any other integer for random: ");
    scanf("%d", &selection);

    if (selection < 1 || selection > 3) {
	selection = rand() % 4;
    }

    print_face(selection);
    return 0;
}

void print_face(int selection) {
    if (selection == 1) {
	printf("Have a nice day! :) \n");
    } else if (selection == 2) {
	printf(":(\n");
    } else if (selection == 3) {
	printf("Meh :\\ \n");
    } else {
	hoo();
    }
}

void hoo() {
    printf(" *___*\n {O,O}\n/)___)\n_\"__\"_\n");
}
