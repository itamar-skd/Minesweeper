#ifndef __GAME_MATRIX_H__
#define __GAME_MATRIX_H__

#include "game_cell.h"
#include <cstdlib>

#define CELL_SIZE 3
#define MATRIX_ROW_START 2

class GameMatrix
{
    public:
        typedef enum : uint8_t {
            REVEAL_OK,
            REVEAL_OUT_OF_BOUNDS,
            REVEAL_BOMB
        } RevealOptions;

    private:
        GameMatrix();
        ~GameMatrix();

    public:
        GameMatrix(GameMatrix const &) = delete;
        GameMatrix& operator=(GameMatrix const &) = delete;

    public: /* cell accessors */
        GameCell& at(int32_t i);
        GameCell& at(int32_t i, int32_t j);

    /* initialization */
    private:
        void __init_bombs();
    
    public:
        void init(size_t matrix_length, size_t matrix_width, size_t num_minefields);

    public: /* interaction */
        static GameMatrix& matrix();
        RevealOptions reveal(int32_t i, int32_t j);
        void print_matrix();

    private:
        GameCell* __cells;
        size_t __matrix_length;
        size_t __matrix_width;
        size_t __num_minefields;
};

#endif /* __GAME_MATRIX_H__ */