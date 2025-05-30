#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include "game_matrix.h"

class UserInterface
{
    public:
        UserInterface();
        ~UserInterface() = default;
    
    private:
        void __handle_reveal_result(GameMatrix::RevealOptions result);
    public:
        void init();
        void run();

    private:
        bool __keep_alive;
};

#endif /* __USER_INTERFACE_H__ */