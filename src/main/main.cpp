#include "print_utils.h"
#include "arg_utils.h"
#include "game_matrix.h"
#include "user_interface.h"
#include <iostream>
#include <ncurses.h>
#include <csignal>

void handle_signal(int signal) {
    UserInterface::cleanup();
    std::exit(signal);
}

int main(int argc, char** argv)
{
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    atexit(UserInterface::cleanup);
    UserInterface::init();

    for (size_t i = 0; i < argc; i++)
    {
        parse_args(argv[i]);
    }

    GameMatrix::matrix().init();
    UserInterface::check_size(GameMatrix::matrix().matrix_length(), GameMatrix::matrix().matrix_width());

    clear();
    refresh();

    UserInterface ui;
    ui.run();
    return 0;
}