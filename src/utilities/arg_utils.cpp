#include "arg_utils.h"
#include "print_utils.h"
#include "game_matrix.h"
#include <ncurses.h>

void print_help_argument(const char* argument, const char* description)
{
    static const int MAX_ARG_LENGTH = 20;

    print_green("--");
    print_green(argument);
    printw("%-*s %s", MAX_ARG_LENGTH - (int)strlen(argument), ":", description);
}

uint32_t get_numerical_argument(std::string& arg_str, const size_t arg_length)
{
    uint32_t value = 0;
    const char* arg = arg_str.c_str() + arg_length + 1; // skip prefix + '='
    size_t i = 0, len = arg_str.size() - (arg_length + 1);

    while (i < len && arg != nullptr && *arg >= '0' && *arg <= '9')
    {
        value = value * 10 + (*arg - '0');
        arg++;
        i++;
    }

    return value;
}

void print_help()
{
    print_green("Welcome to Minesweeper, by Itamar Shaked.\n\n");
    print_blue("Here are some helpful arguments:\n");
    print_help_argument("matrix_length", "set the matrix length (default: 20)\n");
    print_help_argument("matrix_width", "set the matrix width (default: 20)\n");
    print_help_argument("num_minefields", "set the number of minefields to be generated (must be smaller than the area, default: 50)\n");

    print_blue("\nHow to play:\n");
    printw("Minefields are scattered around the matrix. Your objective is to find them.\n");
    printw("Cells that do not contain a minefield will be numbered by the number of minefields they're surrounded by, in the 3x3 square surrounding them.\n");
    printw("Left-clicking a cell will reveal its contents. ");
    print_red("Make sure to only click if you're sure there's no minefield there!\n");
    printw("Right-clicking a cell will place/remove a flag. You should use flags to indicate a minefield in the cell. ");
    print_red("Flagging a cell will not activate the minefield or reveal the cell's contents.\n");
    print_green("\nGood luck and have fun! Press anything to exit.\n");
}

void parse_args(std::string arg)
{
    if (arg.rfind("--help") != std::string::npos)
    {
        print_help();
        refresh();
        getch();
        endwin();
        exit(0);
    }
    else if (arg.rfind("--matrix_length") != std::string::npos)
    {
        uint32_t length = get_numerical_argument(arg, strlen("--matrix_length"));
        GameMatrix::matrix().set_matrix_length(length);
    }
    else if (arg.rfind("--matrix_width") != std::string::npos)
    {
        uint32_t width = get_numerical_argument(arg, strlen("--matrix_width"));
        GameMatrix::matrix().set_matrix_width(width);
    }
    else if (arg.rfind("--num_minefields") != std::string::npos)
    {
        uint32_t num_minefields = get_numerical_argument(arg, strlen("--num_minefields"));
        GameMatrix::matrix().set_num_minefields(num_minefields);
    }

    refresh();
}