#ifndef __GAME_MATRIX_H__
#define __GAME_MATRIX_H__

#include "game_cell.h"
#include <cstdlib>

#define CELL_SIZE 3
#define MATRIX_ROW_START 2

#define MATRIX_LENGTH_DEFAULT 20
#define MATRIX_WIDTH_DEFAULT 20
#define MATRIX_MINEFIELDS_DEFAULT 50

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

    private: /* initialization */
        void __init_bombs();

    public:
        void init();

    public: /* getters */
        inline size_t matrix_length()   { return this->__matrix_length; }
        inline size_t matrix_width()    { return this->__matrix_width; }
        inline size_t num_minefields()  { return this->__num_minefields; }
    public: /* setters */
        inline void set_matrix_length(size_t matrix_length) { this->__matrix_length = matrix_length; }
        inline void set_matrix_width(size_t matrix_width) { this->__matrix_width = matrix_width; }
        inline void set_num_minefields(size_t num_minefields) { this->__num_minefields = num_minefields; }

    public: /* interaction */
        static GameMatrix& matrix();
        RevealOptions reveal(int32_t i, int32_t j, bool check_flags = true);
        void place_flag(int32_t i, int32_t j);
        void print_matrix();

    private:
        GameCell* __cells;
        size_t __matrix_length;
        size_t __matrix_width;
        size_t __num_minefields;
};

#endif /* __GAME_MATRIX_H__ */