#ifndef TETRIS_H
#define TETRIS_H

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20
#define PART_SIZE 4
#define FILENAME "highscore.txt"

typedef enum {
  Start,
  Restart,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  None
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

  int terminate;
  int start;
  int coord_x;
  int coord_y;
  int **part;
  int (*parts)[4][4];
  pthread_mutex_t lock;
} GameInfo_t;

// void userInput(UserAction_t *action, int hold);

GameInfo_t updateCurrentState();

void turnPart(GameInfo_t *gamestate);
int rotateCheck(GameInfo_t *gamestate, int matrix[PART_SIZE][PART_SIZE]);
void calculateInput(UserAction_t input, GameInfo_t *gamestate);
void *user_input(void *arg);
int moveCheck(GameInfo_t *gamestate, int move_v, int move_h);
void checkDeletion(GameInfo_t *gamestate);
void add_score(GameInfo_t *gamestate, int multiplier);
void add_level(GameInfo_t *gamestate);
void deleteRow(GameInfo_t *gamestate, int coord);
void moveDown(GameInfo_t *gamestate);
void addPart(GameInfo_t *gamestate);
void moveRightOrLeft(GameInfo_t *gamestate, int dir);
void *increment_counter(void *arg);
void fill_matrix(int **matrix);
void get_part(int parts[PART_SIZE][PART_SIZE], int **result);
int (*init_parts())[4][4];
void get_memory(int ***result, int rows, int cols);
int init_part(GameInfo_t *result, int parts[PART_SIZE][PART_SIZE]);
void combine_matrix(GameInfo_t *gameinfo, int result[HEIGHT][WIDTH]);
void print_m(int matrix[HEIGHT][WIDTH]);
int get_hiscore();
void check_score(GameInfo_t *gamestate);
int set_hiscore(int value);
void set_defaults(GameInfo_t *gamestate);
void release_all_memory(GameInfo_t *gamestate);
void release_memory(int **array, int rows);
int main_body();
int main();

#endif