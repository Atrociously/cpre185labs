#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include <unistd.h>
#include <termios.h>

typedef struct {
    int code;
    char data;
} result_t;

result_t timeout_getchar(uint32_t wait_millis) {
    struct termios oldt, newt;
    fd_set input_fd;
    struct timeval timeout;

    // disable canonical mode but save attrs to reset after finished
    // this allows us to read single chars without hitting enter
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // get the input file descriptor
    FD_ZERO(&input_fd);
    FD_SET(STDIN_FILENO, &input_fd);

    timeout.tv_sec = 0;
    timeout.tv_usec = wait_millis * 1000;

    int ready = 0;
    ready = select(1, &input_fd, NULL, NULL, &timeout);

    if (ready == -1) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // reset stdin
        return (result_t) { .code = -1, .data = -1 };
    }

    if (ready) {
        char next;
        read(0, &next, 1);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // reset stdin
        return (result_t) { .code = 1, .data = next };
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // reset stdin
        return (result_t) { .code = 0, .data = -1 };
    }
}

int main() {
    srand(time(NULL));
    printf("This is a Bop-It Game\n");

    printf("Please select difficulty\n");
    printf("0: easy\n");
    printf("1: hard\n");
    printf("-> ");

    int difficulty;
    scanf("%d", &difficulty);
    while (difficulty < 0 || difficulty > 1) {
        printf("Please choose a valid difficulty!\n");
        printf("-> ");
        scanf("%d", &difficulty);
    }

    int range_max = 127; // max is exclusive
    int range_min = 32; // min is inclusive
    if (difficulty) {
        range_max = 123;
        range_min = 65;
    }

    int rounds = 0;
    int timeout = 2500;
    while (timeout > 0) {
        char target = rand() % (range_max - range_min) + range_min;
        if (difficulty) {
            char ch = range_min;
            char mid = (range_min + range_max) / 2;
            for (; ch < mid; ch++) {
                char offset = (mid - range_min) + ch;
                printf("%c: %d | %c: %d\n", ch, ch, offset, offset);
            }
            printf("Press the %d key!\n", target);
        } else {
            printf("Press the '%c' key!\n", target);
        }
        printf("You have %d milliseconds to respond!\n", timeout);

        result_t input = timeout_getchar(timeout);
        if (input.code) {
            if (input.data != target) {
                printf("Wrong key! :(\n");
                break;
            }
        } else {
            printf("\nYou ran out of time. :(\n");
            break;
        }
        timeout -= 100;
        rounds += 1;
        printf("\n");
    }

    if (timeout == 0) {
        printf("You beat the game!\n");
        printf("How the hell did you press a button in under 100ms?\n");
    }

    printf("Thanks for playing!\n");
    printf("You made it through %d rounds!", rounds);
}
