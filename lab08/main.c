#include "game.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("enter difficulty as first argument\n");
        return -1;
    }

    double difficulty = atof(argv[1]);
    difficulty /= 100;

    GameState* g = game_init((Options) {
        .difficulty = difficulty,
    });

    while (1) {
        char ch = getch();
        if (ch == 'q') {
            break;
        }
        Input in;
        if (ch == 'a') {
            in.gyro.x = -1;
        } else if (ch == 'd') {
            in.gyro.x = 1;
        } else {
            in.gyro.x = 0;
        }

        game_draw(g);
        game_update(g, in);
        usleep(200000);
    }

    game_free(g);
    return 0;
}
