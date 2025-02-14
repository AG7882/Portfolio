#include "gui.h"

void draw_window(WINDOW *win)
{
    box(win, 0, 0);
    wrefresh(win);
}

void userInput(UserAction_t *action)
{
    int c;

    c = getch();

    switch (c)
    {
    case KEY_UP:
        *action = Up;
        break;
    case KEY_DOWN:
        *action = Down;
        break;
    case KEY_LEFT:

        *action = Left;
        break;
    case KEY_RIGHT:

        *action = Right;
        break;
    case ' ':

        *action = Action;
        break;

    case KEY_BACKSPACE:

        *action = Restart;
        break;
    case KEY_END:

        *action = Terminate;
        break;
    case 'p':

        *action = Pause;
        break;
    case 's':

        *action = Start;
        break;
    default:
        *action = None;
    }
}
void init_nc()
{
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
}
void end_nc() { endwin(); }

void print_score(int score)
{
    mvprintw(SCORE_Y + 1, GUI_INDENTIATION, "%d", score);
    mvprintw(SCORE_Y, GUI_INDENTIATION, "%s", "SCORE");
    refresh();
}

void print_hi_score(int score)
{
    mvprintw(HI_SCORE_Y + 1, GUI_INDENTIATION, "%d", score);
    mvprintw(HI_SCORE_Y, GUI_INDENTIATION, "%s", "HIGH SCORE");
    refresh();
}

void print_level(int level)
{
    mvprintw(LEVEL_Y + 1, GUI_INDENTIATION, "%d", level);
    mvprintw(LEVEL_Y, GUI_INDENTIATION, "%s", "LEVEL");
    refresh();
}

void print_pause_msg()
{
    mvprintw(PAUSE_Y, GUI_PAUSE, "%s", "Game is paused");
    refresh();
}

void print_start_msg()
{
    mvprintw(2, 3, "%s", "     TETRIS     ");
    mvprintw(3, 3, "%s", "                ");
    mvprintw(4, 3, "%s", "Press S to start");
    mvprintw(8, 1, "%s", "Controls:           ");
    mvprintw(9, 1, "%s", "<- and -> to move   ");
    mvprintw(10, 1, "%s", "Space to rotate     ");
    mvprintw(11, 1, "%s", "P to pause          ");
    mvprintw(12, 1, "%s", "Backspace to restart");
    refresh();
}

void less_window(int **matrix)
{
    WINDOW *main_win =
        newwin(LESS_BOX_HEIGHT, LESS_BOX_WIDTH, LESS_BOX_Y, GUI_INDENTIATION);

    draw_window(main_win);

    int value;
    for (int i = 1; i <= PART_SIZE; i++)
    {
        for (int j = 1; j <= PART_SIZE; j++)
        {
            value = matrix[i - 1][j - 1];
            wattrset(main_win, COLOR_PAIR(value));
            mvwaddch(main_win, j, i * 2 - 1, ' ');
            mvwaddch(main_win, j, i * 2, ' ');

            wattrset(main_win, COLOR_PAIR(0));
            draw_window(main_win);
        }
    }
}

void game_window(int matrix[HEIGHT][WIDTH])
{
    WINDOW *main_win = newwin(GAME_BOX_SIZE, GAME_BOX_SIZE, 0, 0);

    draw_window(main_win);

    int value;
    for (int i = 1; i <= HEIGHT; i++)
    {
        for (int j = 1; j <= WIDTH; j++)
        {
            value = matrix[i - 1][j - 1];
            wattrset(main_win, COLOR_PAIR(value));
            mvwaddch(main_win, i, j * 2 - 1, ' ');
            mvwaddch(main_win, i, j * 2, ' ');

            wattrset(main_win, COLOR_PAIR(0));
            draw_window(main_win);
        }
    }
}
