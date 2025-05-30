#include "game_matrix.h"
#include <memory.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

GameCell& GameMatrix::at(int32_t i)
{
    /* If cell is out of bounds, don't crash. Just increment an unused cell. */
    static GameCell out_of_bounds_cell;

    if (i < 0 || i >= this->__matrix_length * this->__matrix_width)
        return out_of_bounds_cell;

    return this->__cells[i];
}

GameCell& GameMatrix::at(int32_t i, int32_t j)
{
    /* If cell is out of bounds, don't crash. Just increment an unused cell. */
    static GameCell out_of_bounds_cell;

    if (i < 0 || i >= this->__matrix_length)
        return out_of_bounds_cell;

    if (j < 0 || j >= this->__matrix_width)
        return out_of_bounds_cell;

    return this->__cells[i * this->__matrix_length + j];
}

void GameMatrix::__init_bombs()
{
    size_t matrix_size = this->__matrix_length * this->__matrix_width;

    /* Generate a list of all matrix indices */
    std::vector<int> pool;
    for (size_t i = 0; i < matrix_size; ++i) {
        pool.push_back(i);
    }

    /* Shuffle the list to randomize the first this->__num_minefields entries */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(pool.begin(), pool.end(), gen);

    /* Take the first this->__num_minefields entries */
    std::vector<size_t> bombs(pool.begin(), pool.begin() + this->__num_minefields);

    for (const size_t& bomb_index : bombs)
    {
        this->__cells[bomb_index].set_bomb();

        /* increment number of bombs for all surrounding cells */
        for (int8_t i = -1; i <= 1; i++)
        {
            for (int8_t j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                    this->at(bomb_index + i * this->__matrix_length + j)++;
            }
        }
    }
}

GameMatrix::GameMatrix(size_t matrix_length, size_t matrix_width, size_t num_minefields)
    : __cells(nullptr)
    , __matrix_length(matrix_length)
    , __matrix_width(matrix_width)
    , __num_minefields(num_minefields)
{

    const size_t matrix_size = matrix_length * matrix_width;
    this->__cells = new GameCell[matrix_size];

    this->__init_bombs();
}

GameMatrix::~GameMatrix()
{
    if (this->__cells != nullptr)
        delete [] this->__cells;
}

void GameMatrix::reveal(int32_t i, int32_t j)
{
    if (i < 0 || i >= this->__matrix_length)
        return;

    if (j < 0 || j >= this->__matrix_length)
        return;

    GameCell& cur_cell = this->at(i, j);
    if (cur_cell.revealed())
        return;

    cur_cell.set_revealed();

    if (cur_cell.is_bomb() || cur_cell.num_surrounding_bombs() > 0)
        return;

    for (int8_t row = -1; row <= 1; row++)
    {
        for (int8_t col = -1; col <= 1; col++)
        {
            if (row != 0 || col != 0)
                this->reveal(i + row, j + col);
        }
    }
}

void GameMatrix::print_matrix()
{
    for (size_t i = 0; i < this->__matrix_length; i++)
    {
        for (size_t j = 0; j < this->__matrix_width; j++)
        {
            const GameCell& cell = this->at(i, j);
            std::string to_print = " ";

            if (cell.revealed())
            {
                if (cell.is_bomb())
                    to_print = "\033[31mX\033[0m";  /* red X indicating bomb */
                else
                    to_print = std::to_string(cell.num_surrounding_bombs());
            }

            /* Always print fixed-width (3 columns) */
            std::cout << std::setw(3) << to_print;
        }

        std::cout << std::endl;
    }
}