#ifndef __GAME_MATRIX_H__
#define __GAME_MATRIX_H__

#include "game_cell.h"
#include <cstdlib>

class GameMatrix
{
    private: /* cell accessors */
        GameCell& at(int32_t i);
        GameCell& at(int32_t i, int32_t j);

    private: /* initialization */
        void __init_bombs();

    public:
        GameMatrix(size_t matrix_length, size_t matrix_width, size_t num_minefields);
        ~GameMatrix();

    public:
        void reveal(int32_t i, int32_t j);
        void print_matrix();

    private:
        GameCell* __cells;
        size_t __matrix_length;
        size_t __matrix_width;
        size_t __num_minefields;
};

#endif /* __GAME_MATRIX_H__ */