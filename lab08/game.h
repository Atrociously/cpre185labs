#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "types.h"
#include "gameutil.h"

#define AVATAR 'A'
#define WALL '*'
#define EMPTY ' '

GameState* game_init(Options);

void game_update(GameState*, Input);
void game_draw(GameState*);

void game_free(GameState*);

#endif
