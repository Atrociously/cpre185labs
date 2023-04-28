#include <stdio.h>
#include <time.h>
#include <stdlib.h> // fixed added lib for rand

char ask_to_play(int times_played);
int select_random_number();
void run_game(int computer_number); // fixed missing prototype declaration

int main(int argc, char *argv[]) {
    char prompt = '-';
    int played = 0, computer_guess = 0;

    prompt = ask_to_play(played);
    played = 1;

    while (prompt == 'y') {
	computer_guess = select_random_number();
	run_game(computer_guess);
	//prompt = ask_to_play(playd);
	prompt = ask_to_play(played); // fixed incorrect variable name
    }
    printf("\n\nThanks for playing!\n");
    return 0;
}

char ask_to_play(int played_before) {
    char yes_or_no;
    if (!played_before) {
	printf("Do you want to play a game? "
	       "Enter 'y' to play, anything else not to play. :(\n  -> ");
	//scanf(" %c", yes_or_no);
	scanf(" %c", &yes_or_no); // fixed added pointer
    } else {
	scanf(" %c", &yes_or_no);
    }
    printf("%c", yes_or_no);
    return yes_or_no;
}

int select_random_number() {
    srand(time(NULL));
    return rand() % 100;
}

void run_game(int computer_number) {
    int number = 0;
    int correct = 0; // fixed missing variable declaration

    printf("\n\nYou are guessing a number. The options are 1 through 100.\n\n");
    printf("What is your guess on what number I will select?\n  -> ");
    //scanf("%c", &number);
    scanf("%d", &number); // fixed bad input format
    
    while (!correct) {
	if (number < 1 || number > 100) {
	    printf("\nYour number is not within the correct range of numbers. Guess again\n  -> ");
	//} else  if (number = computer_number) {
    	} else if (number == computer_number) { // fixed incorrect if expression assignment
	    printf("\nThe number was %d!\n", computer_number);
	    printf("\nYou guessed the number correctly!\n\n"
		   "Do you want to play again? ('y' for yes)\n  -> ");
	    correct = 1;
	} else if (number < computer_number) {
	    printf("\nYou guessed too low. Enter another guess.\n  -> ");
	} else {
	    printf("\nYou guessed too high. Enter another guess.\n -> ");
	}
    	scanf("%d", &number);
    }
}
