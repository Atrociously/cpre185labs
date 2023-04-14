#ifndef GAMEUTIL_H
#define GAMEUTIL_H

#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>
#include "types.h"

/**
 * Return the minimum of two input values
 */
double min(double, double);

/**
 * Return the maximum of two input values
 */
double max(double, double);

/**
 * Return a random number either 0 or 1
 * biased by the input double.
 * bias of 0 = all zeros
 * bias of 1 = all ones
 * bias of 0.5 = 50% zeros 50% ones
 */
int biased_rand(double);

void draw_char(size_t x, size_t y, char ch);

void parse_input(const char*, Input*);

void wait_millis(size_t now, size_t millis);

#endif
