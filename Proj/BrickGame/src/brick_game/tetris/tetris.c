#include "tetris.h"

#include "../../gui/cli/gui.h"

void turnPart(GameInfo_t *gamestate) {
  int res[PART_SIZE][PART_SIZE];
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      res[i][j] = 0;
    }
  }
  for (int i = 0; i < PART_SIZE - 1; i++) {
    for (int j = 0; j < PART_SIZE - 1; j++) {
      res[2 - j][i] = gamestate->part[i][j];
    }
  }
  for (int k = 3; k >= 0; k--) {
    res[k][3] = gamestate->part[3][k];
    res[3][k] = gamestate->part[k][3];
  }
  if (rotateCheck(gamestate, res) == 0)

  {
    for (int i = 0; i < PART_SIZE; i++) {
      for (int j = 0; j < PART_SIZE; j++) {
        gamestate->part[i][j] = res[i][j];
      }
    }
  }
}

int rotateCheck(GameInfo_t *gamestate, int matrix[PART_SIZE][PART_SIZE]) {
  int res = 0;
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      if (matrix[i][j] != 0 &&
          (gamestate->coord_x + i < 0 || gamestate->coord_x + i >= WIDTH ||
           gamestate->field[gamestate->coord_x + i][gamestate->coord_y + j] !=
               0)) {
        res = 1;
      }
    }
  }
  return res;
}

void calculateInput(UserAction_t input, GameInfo_t *gamestate) {
  if (!gamestate->start && input != Terminate) {
    if (!gamestate->pause) {
      switch (input) {
        case Right:

          moveRightOrLeft(gamestate, 1);
          break;
        case Left:

          moveRightOrLeft(gamestate, -1);
          break;

        case Down:

          moveDown(gamestate);
          break;
        case Action:

          turnPart(gamestate);
          break;
        case Pause:

          gamestate->pause = abs(gamestate->pause - 1);
          break;
        case Start:

          break;
        case Restart:
          release_all_memory(gamestate);
          set_defaults(gamestate);

          break;

        default:
          break;
      }
    } else {
      switch (input) {
        case Pause:

          gamestate->pause = abs(gamestate->pause - 1);
          break;
        case Terminate:

          gamestate->terminate = 1;
          break;
        default:
          break;
      }
    }
  } else {
    switch (input) {
      case Start:

        gamestate->start = 0;
        break;
      case Terminate:

        gamestate->terminate = 1;
        break;
      default:
        break;
    }
  }
}

void *user_input(void *arg) {
  GameInfo_t *gameInfo = (GameInfo_t *)arg;
  UserAction_t input = Pause;
  int matrix[HEIGHT][WIDTH];
  do {
    combine_matrix(gameInfo, matrix);

    userInput(&input);

    pthread_mutex_lock(&gameInfo->lock);
    calculateInput(input, gameInfo);
    pthread_mutex_unlock(&gameInfo->lock);

  } while (!gameInfo->terminate);

  return 0;
}

int moveCheck(GameInfo_t *gamestate, int move_v, int move_h) {
  int res = 0;
  int y, x;

  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      y = gamestate->coord_y + i + move_v;
      x = gamestate->coord_x + j + move_h;

      if (gamestate->part[j][i] != 0 &&
          ((x >= WIDTH) || (y >= HEIGHT) || (x < 0) ||
           gamestate->field[y][x] != 0)) {
        return res = 1;
      }
    }
  }
  return res;
}

void checkDeletion(GameInfo_t *gamestate) {
  int addscore = 0;
  int res;
  for (size_t i = 0; i < HEIGHT; i++) {
    res = 1;
    for (size_t j = 0; j < WIDTH; j++) {
      if (gamestate->field[i][j] == 0) {
        res = 0;
      }
    }
    if (res) {
      deleteRow(gamestate, i);
      addscore++;
    }
  }
  add_score(gamestate, addscore);
  print_score(gamestate->score);
  print_hi_score(gamestate->high_score);
}
void add_score(GameInfo_t *gamestate, int multiplier) {
  switch (multiplier) {
    case 1:
      gamestate->score = gamestate->score + 100;
      break;
    case 2:
      gamestate->score = gamestate->score + 300;
      break;
    case 3:
      gamestate->score = gamestate->score + 700;
      break;
    case 4:
      gamestate->score = gamestate->score + 1500;
      break;

    default:
      break;
  }
  add_level(gamestate);
  check_score(gamestate);
}

void add_level(GameInfo_t *gamestate) {
  int level = 0;
  if (gamestate->score < 600) {
    level = 1;
  } else {
    level = gamestate->score / 600 + 1;
  }

  if (level > 10) {
    level = 10;
  }
  gamestate->level = level;
  gamestate->speed = 200000000 + (200000000 / level);
  print_level(gamestate->level);
}

void deleteRow(GameInfo_t *gamestate, int coord) {
  for (size_t i = coord; i > 0; i--) {
    for (size_t j = 0; j < WIDTH; j++) {
      gamestate->field[i][j] = gamestate->field[i - 1][j];
    }
  }
}

void moveDown(GameInfo_t *gamestate) {
  int res = gamestate->coord_y;
  res++;

  if (moveCheck(gamestate, 1, 0) == 0) {
    gamestate->coord_y = res;
  } else {
    addPart(gamestate);
    checkDeletion(gamestate);

    if (init_part(gamestate, gamestate->parts[(rand() % 6)]) == 1) {
      set_hiscore(gamestate->high_score);
      gamestate->start = 1;
      release_all_memory(gamestate);
      set_defaults(gamestate);
    } else {
      less_window(gamestate->next);
    }
  }
}

void addPart(GameInfo_t *gamestate) {
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      if (gamestate->part[j][i] != 0) {
        gamestate->field[i + gamestate->coord_y][j + gamestate->coord_x] =
            gamestate->part[j][i];
      }
    }
  }
}

void moveRightOrLeft(GameInfo_t *gamestate, int dir) {
  int res = gamestate->coord_x;
  res = res + dir;
  if (moveCheck(gamestate, 0, dir) == 0) {
    gamestate->coord_x = res;
  }
}
void *increment_counter(void *arg) {
  GameInfo_t *gameInfo = (GameInfo_t *)arg;
  int matrix[HEIGHT][WIDTH];
  struct timespec time = {0};
  time.tv_nsec = gameInfo->speed;

  do {
    if (gameInfo->start) {
    } else if (!gameInfo->pause) {
      pthread_mutex_lock(&gameInfo->lock);
      moveDown(gameInfo);

      combine_matrix(gameInfo, matrix);
      print_m(matrix);
      less_window(gameInfo->next);
      time.tv_nsec = gameInfo->speed;
      pthread_mutex_unlock(&gameInfo->lock);

      nanosleep(&time, NULL);
    } else {
      print_pause_msg();
    }
  } while (!gameInfo->terminate);

  return 0;
}

void fill_matrix(int **matrix) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      matrix[i][j] = 0;
    }
  }
}

void get_part(int parts[PART_SIZE][PART_SIZE], int **result) {
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      result[i][j] = parts[i][j];
    }
  }
}

int (*init_parts())[4][4] {
  static int parts[6][4][4] = {

      {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 2, 0, 0}, {0, 2, 0, 0}, {2, 2, 0, 0}, {0, 0, 0, 0}},

      {{0, 3, 0, 0}, {0, 3, 0, 0}, {0, 3, 3, 0}, {0, 0, 0, 0}},

      {{0, 4, 4, 0}, {4, 4, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{5, 5, 0, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},

      {{0, 6, 0, 0}, {6, 6, 6, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};

  return parts;
}

void get_memory(int ***result, int rows, int cols) {
  *result = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    (*result)[i] = malloc(cols * sizeof(int));
  }
}

int init_part(GameInfo_t *result, int parts[PART_SIZE][PART_SIZE]) {
  int res = 0;

  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      result->part[i][j] = result->next[i][j];
    }
  }
  result->coord_x = 3;
  result->coord_y = 0;
  get_part(parts, result->next);
  if (moveCheck(result, 0, 0) == 1) {
    res = 1;
  }
  return res;
}

void combine_matrix(GameInfo_t *gameinfo, int result[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      result[i][j] = gameinfo->field[i][j];
    }
  }

  for (int i2 = 0; i2 < PART_SIZE; i2++) {
    for (int j2 = 0; j2 < PART_SIZE; j2++) {
      if (gameinfo->part[i2][j2] != 0) {
        result[j2 + gameinfo->coord_y][i2 + gameinfo->coord_x] =
            gameinfo->part[i2][j2];
      }
    }
  }
}

void print_m(int matrix[HEIGHT][WIDTH]) { game_window(matrix); }

int get_hiscore() {
  FILE *file;
  int value;

  file = fopen(FILENAME, "r");
  if (file != NULL) {
    if (fscanf(file, "%d", &value) != 1) {
      value = 0;
    }
    fclose(file);
  } else {
    value = 0;
  }

  return value;
}

void check_score(GameInfo_t *gamestate) {
  if (gamestate->score > gamestate->high_score) {
    gamestate->high_score = gamestate->score;
  }
}

int set_hiscore(int value) {
  int ex_code = 1;
  FILE *file;

  file = fopen(FILENAME, "w");
  if (file == NULL) {
    return 0;
  }

  if (fprintf(file, "%d", value) < 0) {
    ex_code = 0;
  }

  fclose(file);
  return ex_code;
}

void set_defaults(GameInfo_t *gamestate) {
  pthread_mutex_init(&gamestate->lock, NULL);

  gamestate->parts = init_parts();
  get_memory(&gamestate->field, HEIGHT, WIDTH);
  get_memory(&gamestate->next, PART_SIZE, PART_SIZE);
  get_memory(&gamestate->part, PART_SIZE, PART_SIZE);

  get_part(gamestate->parts[(rand() % 6)], gamestate->next);
  init_part(gamestate, gamestate->parts[(rand() % 6)]);

  gamestate->start = 1;
  gamestate->pause = 0;
  gamestate->score = 0;
  gamestate->high_score = get_hiscore();
  gamestate->level = 1;
  gamestate->speed = 400000000;
  gamestate->terminate = 0;

  fill_matrix(gamestate->field);
  print_score(gamestate->score);
  print_start_msg();
}

void release_all_memory(GameInfo_t *gamestate) {
  release_memory(gamestate->field, HEIGHT);
  release_memory(gamestate->next, PART_SIZE);
  release_memory(gamestate->part, PART_SIZE);
}

void release_memory(int **array, int rows) {
  for (int i = 0; i < rows; i++) {
    free(array[i]);
  }
  free(array);
}

int main_body() {
  srand(time(NULL));
  init_nc();
  GameInfo_t gamestate;

  set_defaults(&gamestate);

  pthread_t input_thread, increment_thread;

  fill_matrix(gamestate.field);
  int matrix[HEIGHT][WIDTH];

  combine_matrix(&gamestate, matrix);

  print_score(gamestate.score);
  print_hi_score(gamestate.high_score);
  print_level(gamestate.level);

  pthread_create(&input_thread, NULL, user_input, &gamestate);
  pthread_create(&increment_thread, NULL, increment_counter, &gamestate);

  pthread_join(input_thread, NULL);
  pthread_join(increment_thread, NULL);

  release_all_memory(&gamestate);

  end_nc();
  return 0;
}

#ifndef TEST_MODE
int main() {
  main_body();
  return 0;
}
#endif