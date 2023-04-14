#include "game.h"
#include <curses.h>

void init_maze(GameState* g) {
    // allocate and fill maze memory with random maze data
    g->maze = calloc(g->data.max_rows, sizeof(char*));
    for (size_t row = 0; row < g->data.max_rows; row++) {
        g->maze[row] = calloc(g->data.max_cols, sizeof(char));
        for(size_t col = 0; col < g->data.max_cols; col++) {
            int is_wall = biased_rand(g->data.difficulty);
            if (is_wall) {
                g->maze[row][col] = WALL;
            } else {
                g->maze[row][col] = EMPTY;
            }
        }
    }
}

void init_player(GameState* g) {
    g->player.pos.x = g->data.max_cols / 2 - 1;
    g->player.pos.y = 0;
}

GameState* game_init(Options opts) {
    GameState* g = calloc(1, sizeof(GameState));

    g->data = opts;
    srand(time(NULL));
    initscr();
    refresh();
    curs_set(0);
    nodelay(stdscr, 1); // remove when input from controller
    noecho();           // can remove when input from controller

    getmaxyx(stdscr, g->data.max_rows, g->data.max_cols);
    
    init_player(g);
    init_maze(g);

    return g;
}

void game_update(GameState* g, Input input) {
    Point player_next = g->player.pos;

    if (input.gyro.x < -0.2) {
        // move left
        if (g->maze[player_next.y][player_next.x-1] != WALL && player_next.x-1 != (size_t)-1) {
            player_next.x -= 1;
        }
    } else if (input.gyro.x > 0.2) {
        // move right
        if (player_next.x+1 < g->data.max_cols && g->maze[player_next.y][player_next.x+1] != WALL) {
            player_next.x += 1;
        }
    }

    if (player_next.y+1 < g->data.max_rows && g->maze[player_next.y+1][player_next.x] != WALL ) {
        player_next.y += 1;
    }
    g->player.pos = player_next;
}

void game_draw(GameState* g) {
    // draw maze
    for (size_t row = 0; row < g->data.max_rows; row++) {
        for (size_t col = 0; col < g->data.max_cols; col++) {
            // don't draw over the player
            if (row == g->player.pos.y && col == g->player.pos.x) {
                continue;
            }
            draw_char(col, row, g->maze[row][col]);
        }
    }
    
    // draw player
    draw_char(g->player.pos.x, g->player.pos.y, AVATAR);
    refresh();
}

void game_free(GameState* g) {
    for (size_t row = 0; row < g->data.max_rows; row++) {
        free(g->maze[row]);
    }
    free(g->maze);
}
