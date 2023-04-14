#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    size_t max_rows;
    size_t max_cols;
    double difficulty;
} Options;

typedef struct {
    size_t x;
    size_t y;
} Point;

typedef struct {
    Point pos;
} Player;

typedef struct {
    char** maze;
    Player player;
    Options data;
} GameState;

typedef struct {
    double x;
    double y;
    double z;
} InputVec;

typedef struct {
    size_t timestamp;
    InputVec accel;
    InputVec gyro;
} Input;

#endif
