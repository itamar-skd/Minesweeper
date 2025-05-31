#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include "game_matrix.h"

class UserInterface
{
    public:
        UserInterface();
        ~UserInterface();
    
    private:
        void __check_winner();
        void __handle_reveal_result(GameMatrix::RevealOptions result);
    public:
        static void init();
        static void cleanup();
        static void check_size(size_t num_row, size_t num_col);
        void run();

    private:
        bool __keep_alive;
        bool __matrix_revealed;
        bool __player_won;
};

#endif /* __USER_INTERFACE_H__ */