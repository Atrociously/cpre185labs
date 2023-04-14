#include "game.h"
#include "gameutil.h"

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

/// 0 is all zeros
/// 0.5 is 50/50
/// 1 is all ones
int biased_rand(double bias) {
    const int R = 100;
    bias = min(max(bias, 0), 1);
    int val = rand() % R + 1;
    int mid = R - (R * bias);
    return val <= mid ? 0 : 1;
}

void draw_char(size_t x, size_t y, char ch) {
    mvaddch(y, x, ch);
}

void parse_input(const char* line, Input* input) {
    sscanf(line, "%ld, %lf, %lf, %lf",
           &input->timestamp,
           &input->gyro.x,
           &input->gyro.y,
           &input->gyro.z
           );
}

void wait_millis(size_t now, size_t millis) {
    #define BUFSIZE 100

    size_t target = now + millis;

    char s[BUFSIZE];
    fgets(s, BUFSIZE, stdin);
    Input in;
    parse_input(s, &in);
    while (in.timestamp < target) {
        fpurge(stdin);
        fgets(s, 100, stdin);
        parse_input(s, &in);
    }
}
