#include "user_interface.h"
#include "print_utils.h"
#include <ncurses.h>

UserInterface::UserInterface()
    : __keep_alive(true)
    , __matrix_revealed(false)
{}

UserInterface::~UserInterface()
{
    this->cleanup();
}

void UserInterface::__handle_reveal_result(GameMatrix::RevealOptions result)
{
    switch (result)
    {
        case GameMatrix::RevealOptions::REVEAL_BOMB:
            this->__keep_alive = false;
        case GameMatrix::RevealOptions::REVEAL_OK:
            clear();
            GameMatrix::matrix().print_matrix();
            refresh();
            this->__matrix_revealed = true;
        case GameMatrix::RevealOptions::REVEAL_OUT_OF_BOUNDS:
        default:
            break;
    }
}

void UserInterface::init()
{
    initscr(); /* initialize curses mode */
    use_default_colors();
    start_color();
    keypad(stdscr, TRUE); // Enable special keys (arrows, etc.)
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    noecho();
    cbreak();
    resize_term(0, 0);
    curs_set(0);
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_BLUE, -1);
    init_pair(3, COLOR_GREEN, -1);
}

void UserInterface::cleanup()
{
    clear();
    refresh();
    endwin();
}

void UserInterface::check_size(size_t num_row, size_t num_col)
{
    int term_rows, term_cols;
    getmaxyx(stdscr, term_rows, term_cols);

    int required_rows = MATRIX_ROW_START + num_row;
    int required_cols = num_col * CELL_SIZE;

    if (term_rows < required_rows || term_cols < required_cols)
    {
        endwin();
        attron(COLOR_PAIR(1));
        printw("Terminal too small. Need at least %d rows x %d columns.\n", required_rows, required_cols);
        attroff(COLOR_PAIR(1));
        getch();
        exit(1);
    }
}

void UserInterface::run()
{
    MEVENT event;

    while (this->__keep_alive) {
        int ch = getch();
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                int32_t row = event.y - MATRIX_ROW_START;
                int32_t col = (event.x + 1) / CELL_SIZE - 1;

                /* explode minefield is left clicked */
                if (event.bstate & BUTTON1_CLICKED)
                {
                    GameMatrix::RevealOptions res = GameMatrix::matrix().reveal(row, col);

                    this->__handle_reveal_result(res);
                }
                /* place flag if right clicked */
                else if ((event.bstate & BUTTON3_CLICKED) && this->__matrix_revealed)
                {
                    GameMatrix::matrix().place_flag(row, col);

                    clear();
                    GameMatrix::matrix().print_matrix();
                    refresh();
                }
            }
        }
        else if (ch == 'q')
            break;
    }

    move(0, 0);
    attron(COLOR_PAIR(1));
    printw("GAME OVER! EXPLODED!!!\n");
    attroff(COLOR_PAIR(1));
    printw("Press anything to exit.");
    refresh();
    getch();
}