#include "print_utils.h"
#include <ncurses.h>

void print_color(int color, const char* to_print)
{
    attron(COLOR_PAIR(color));
    printw("%s", to_print);
    attroff(COLOR_PAIR(color));
}

void print_red(const char* to_print)
{
    print_color(1, to_print);
}

void print_blue(const char* to_print)
{
    print_color(2, to_print);
}

void print_green(const char* to_print)
{
    print_color(3, to_print);
}