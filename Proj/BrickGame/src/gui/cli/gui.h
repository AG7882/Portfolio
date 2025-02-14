#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../brick_game/tetris/tetris.h"

#define WIDTH 10
#define HEIGHT 20
#define GAME_BOX_SIZE 22
#define LESS_BOX_HEIGHT 6
#define LESS_BOX_WIDTH 10
#define GUI_INDENTIATION 26
#define LESS_BOX_Y 1
#define PAUSE_Y 8
#define SCORE_Y 8
#define HI_SCORE_Y 11
#define LEVEL_Y 14
#define GUI_PAUSE 4

void draw_window(WINDOW *win);

// UserAction_t listen_to_user();

void init_nc();
void end_nc();

void game_window(int matrix[HEIGHT][WIDTH]);
void userInput(UserAction_t *action);
void print_score(int score);

void print_hi_score(int score);
void print_level(int level);
void print_pause_msg();
void print_start_msg();
void less_window(int **matrix);

#endif