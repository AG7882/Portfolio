#include <check.h>

#include "brick_game/tetris/tetris.h"
#include "gui/cli/gui.h"

START_TEST(test_turnPart) {
  GameInfo_t gamestate;

  set_defaults(&gamestate);

  int initial_part[PART_SIZE][PART_SIZE] = {
      {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      gamestate.part[i][j] = initial_part[i][j];
    }
  }

  turnPart(&gamestate);

  int expected_part[PART_SIZE][PART_SIZE] = {
      {0, 0, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      ck_assert_int_eq(gamestate.part[i][j], expected_part[i][j]);
    }
  }
}

START_TEST(test_inputs) {
  GameInfo_t gamestate;

  set_defaults(&gamestate);

  calculateInput(Start, &gamestate);
  ck_assert_int_eq(gamestate.start, 0);
  calculateInput(Pause, &gamestate);
  ck_assert_int_eq(gamestate.pause, 1);
  calculateInput(Pause, &gamestate);
  ck_assert_int_eq(gamestate.pause, 0);
  calculateInput(Terminate, &gamestate);
  ck_assert_int_eq(gamestate.terminate, 1);

  set_defaults(&gamestate);
  calculateInput(Start, &gamestate);
  calculateInput(Right, &gamestate);
  ck_assert_int_eq(gamestate.coord_x, 4);
  calculateInput(Left, &gamestate);
  ck_assert_int_eq(gamestate.coord_x, 3);
  calculateInput(Down, &gamestate);
  ck_assert_int_eq(gamestate.coord_y, 1);

  set_defaults(&gamestate);
  calculateInput(Start, &gamestate);

  int initial_part[PART_SIZE][PART_SIZE] = {
      {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      gamestate.part[i][j] = initial_part[i][j];
    }
  }

  calculateInput(Action, &gamestate);

  int expected_part[PART_SIZE][PART_SIZE] = {
      {0, 0, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      ck_assert_int_eq(gamestate.part[i][j], expected_part[i][j]);
    }
  }

  set_defaults(&gamestate);
  gamestate.score = 5;
  calculateInput(Start, &gamestate);
  calculateInput(Restart, &gamestate);
  ck_assert_int_eq(gamestate.score, 0);
  calculateInput(Start, &gamestate);
  calculateInput(Pause, &gamestate);
  calculateInput(Terminate, &gamestate);
  ck_assert_int_eq(gamestate.terminate, 1);
}

START_TEST(test_deletion) {
  GameInfo_t gamestate;

  set_defaults(&gamestate);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gamestate.field[i][j] = 0;
    }
  }

  for (int j1 = 0; j1 < WIDTH; j1++) {
    gamestate.field[HEIGHT - 1][j1] = 1;
  }
  checkDeletion(&gamestate);

  for (int j2 = 0; j2 < WIDTH; j2++) {
    ck_assert_int_eq(gamestate.field[HEIGHT - 1][j2], 0);
  }
}

START_TEST(test_moveDown) {
  GameInfo_t gamestate;

  set_defaults(&gamestate);
  gamestate.start = 0;
  for (int i = 0; i < HEIGHT; i++) {
    gamestate.field[i][3] = 1;
  }

  moveDown(&gamestate);
  ck_assert_int_eq(gamestate.start, 1);
}

START_TEST(test_combine) {
  GameInfo_t gamestate;

  set_defaults(&gamestate);

  gamestate.coord_x = 0;

  int matrix[HEIGHT][WIDTH];

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gamestate.field[i][j] = 0;
    }
  }

  int part[PART_SIZE][PART_SIZE] = {
      {1, 1, 0, 0}, {1, 1, 4, 0}, {0, 0, 0, 0}, {0, 0, 7, 8}};
  for (int i = 0; i < PART_SIZE; i++) {
    for (int j = 0; j < PART_SIZE; j++) {
      gamestate.part[i][j] = part[i][j];
    }
  }
  combine_matrix(&gamestate, matrix);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      ck_assert_int_eq(0, gamestate.field[i][j]);
    }
  }
}

START_TEST(test_threads) {
  srand(time(NULL));

  GameInfo_t gamestate;

  set_defaults(&gamestate);

  pthread_t input_thread, increment_thread;
  gamestate.terminate = 1;
  pthread_create(&input_thread, NULL, user_input, &gamestate);
  pthread_create(&increment_thread, NULL, increment_counter, &gamestate);

  pthread_join(input_thread, NULL);
  pthread_join(increment_thread, NULL);

  release_all_memory(&gamestate);

  ck_assert_int_eq(0, 0);  // если напортачил с логикой то будет выполняться
                           // бесконечно а значит и тест не пройдет
}

Suite *tetr_test(void) {
  Suite *suite = suite_create("TESTS");
  TCase *tcase_ttr = tcase_create("tetris");
  tcase_add_test(tcase_ttr, test_turnPart);
  tcase_add_test(tcase_ttr, test_inputs);
  tcase_add_test(tcase_ttr, test_deletion);
  tcase_add_test(tcase_ttr, test_moveDown);
  tcase_add_test(tcase_ttr, test_combine);
  tcase_add_test(tcase_ttr, test_threads);
  suite_add_tcase(suite, tcase_ttr);
  return suite;
}

int main(void) {
  int count = 0;
  Suite *s = tetr_test();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
