#include "user_interface.h"
#include <ncurses.h>

UserInterface::UserInterface()
    : __keep_alive(true)
{}

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
    curs_set(0);
    init_pair(1, COLOR_RED, -1);
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
                GameMatrix::RevealOptions res = GameMatrix::matrix().reveal(row, col);

                this->__handle_reveal_result(res);
                // break; // or handle based on event.bstate
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
    getch();

    endwin(); // End curses mode
}