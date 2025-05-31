#include "game_matrix.h"
#include <memory.h>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ncurses.h>

GameMatrix::GameMatrix()
    : __cells(nullptr)
    , __matrix_length(0)
    , __matrix_width(0)
    , __num_mines(0)
    , __num_flags(0)
    , __num_correctly_revealed(0)
{}

GameMatrix::~GameMatrix()
{
    if (this->__cells != nullptr)
        delete [] this->__cells;
}

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

    if (i < 0 || j < 0)
        return out_of_bounds_cell;

    if (i * this->__matrix_width + j >= this->__matrix_length * this->__matrix_width)
        return out_of_bounds_cell;

    return this->__cells[i * this->__matrix_width + j];
}

void GameMatrix::__init_bombs()
{
    size_t matrix_size = this->__matrix_length * this->__matrix_width;

    /* Generate a list of all matrix indices */
    std::vector<int> pool;
    for (size_t i = 0; i < matrix_size; ++i) {
        pool.push_back(i);
    }

    /* Shuffle the list to randomize the first this->__num_mines entries */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(pool.begin(), pool.end(), gen);

    /* Take the first this->__num_mines entries */
    std::vector<size_t> bombs(pool.begin(), pool.begin() + this->__num_mines);

    for (const size_t& bomb_index : bombs)
    {
        this->__cells[bomb_index].set_bomb();

        /* increment number of bombs for all surrounding cells */
        for (int8_t i = -1; i <= 1; i++)
        {
            for (int8_t j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                    this->at(bomb_index + i * this->__matrix_width + j)++;
            }
        }
    }
}

void GameMatrix::init()
{
    this->__matrix_length = this->__matrix_length == 0 ? MATRIX_LENGTH_DEFAULT : this->__matrix_length;
    this->__matrix_width = this->__matrix_width == 0 ? MATRIX_WIDTH_DEFAULT : this->__matrix_width;
    if (this->__num_mines == 0 || this->__num_mines >= this->__matrix_length * this->__matrix_width)
        this->__num_mines = MATRIX_MINES_DEFAULT;

    this->__cells = new GameCell[__matrix_length * __matrix_width];

    this->__init_bombs();
}

GameMatrix& GameMatrix::matrix()
{
    static GameMatrix _matrix;
    return _matrix;
}

GameMatrix::RevealOptions GameMatrix::reveal(int32_t i, int32_t j, bool check_flags)
{
    if (i < 0 || i >= this->__matrix_length)
        return RevealOptions::REVEAL_OUT_OF_BOUNDS;

    if (j < 0 || j >= this->__matrix_width)
        return RevealOptions::REVEAL_OUT_OF_BOUNDS;

    static bool first_reveal = true;
    GameCell* cur_cell = &this->at(i, j);

    if (first_reveal)
    {
        while (cur_cell->is_bomb() || cur_cell->num_surrounding_bombs() > 0)
        {
            // memset(this->__cells, 0, sizeof(GameCell) * this->__matrix_length * this->__matrix_length);
            for (size_t i = 0; i < this->__matrix_length * this->__matrix_width; i++)
            {
                this->at(i).clear();
            }
            this->__init_bombs();
            cur_cell = &this->at(i, j);
        }

        first_reveal = false;
    }

    if (cur_cell->is_flag())
        return RevealOptions::REVEAL_OK;

    /* if the player clicked on an already revealed cell, it means they want to reveal the cells around it. */
    /* this is only allowed if the player already flagged all of the mines around the cell. */
    if (cur_cell->revealed())
    {
        if (check_flags)
        {
            RevealOptions reveal_status;

            size_t num_surrounding_flags = 0;
            for (int8_t row = -1; row <= 1; row++)
            {
                for (int8_t col = -1; col <= 1; col++)
                {
                    if ((row != 0 || col != 0) && this->at(i + row, j + col).is_flag())
                        num_surrounding_flags++;
                }
            }

            if (num_surrounding_flags >= cur_cell->num_surrounding_bombs())
            {
                for (int8_t row = -1; row <= 1; row++)
                {
                    for (int8_t col = -1; col <= 1; col++)
                    {
                        if ((row != 0 || col != 0) && !this->at(i + row, j + col).is_flag())
                            if (this->reveal(i + row, j + col, false) == RevealOptions::REVEAL_BOMB)
                                reveal_status = RevealOptions::REVEAL_BOMB;
                    }
                }
            }

            return reveal_status;
        }

        return RevealOptions::REVEAL_OK;
    }

    cur_cell->set_revealed();

    if (cur_cell->is_bomb())
        return RevealOptions::REVEAL_BOMB;

    /* There is only one case where the cells around the selected cell should be recursively opened */
    /* and that is if the cell has no bombs around it (safe to open) */
    if (cur_cell->num_surrounding_bombs() == 0)
    {
        for (int8_t row = -1; row <= 1; row++)
        {
            for (int8_t col = -1; col <= 1; col++)
            {
                if (row != 0 || col != 0)
                    this->reveal(i + row, j + col, false);
            }
        }
    }

    this->__num_correctly_revealed++;
    return RevealOptions::REVEAL_OK;
}

void GameMatrix::place_flag(int32_t i, int32_t j)
{
    if (i < 0 || i >= this->__matrix_length)
        return;

    if (j < 0 || j >= this->__matrix_length)
        return;

    GameCell& cell = this->at(i, j);
    if (cell.revealed())
        return;

    cell.set_flag(!cell.is_flag());
    if (cell.is_flag())
    {
        this->__num_flags++;
        if (cell.is_bomb())
            this->__num_correctly_revealed++;
    }
    else
        this->__num_flags--;
}

void GameMatrix::print_matrix()
{
    clear();
    refresh();
    move(MATRIX_ROW_START, 0);

    for (size_t i = 0; i <= this->__matrix_length + 1; i++)
        printw("%*s", CELL_SIZE, "*");

    for (size_t i = 0; i < this->__matrix_length; i++)
    {
        printw("\n%*s", CELL_SIZE, "*");
        for (size_t j = 0; j < this->__matrix_width; j++)
        {
            std::stringstream ss;
            const GameCell& cell = this->at(i, j);
            std::string to_print = " ";

            if (cell.revealed() || cell.is_flag())
            {
                if (cell.is_flag())
                {
                    to_print = "F";
                    attron(COLOR_PAIR(2));
                }
                else if (cell.is_bomb())
                {
                    to_print = "X";  /* red X indicating bomb */
                    attron(COLOR_PAIR(1));
                }
                else
                    to_print = std::to_string(cell.num_surrounding_bombs());
            }

            /* Always print fixed-width (3 columns) */
            ss << std::setw(CELL_SIZE) << to_print;
            printw("%*s", CELL_SIZE, to_print.c_str());
            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
        }
        printw("%*s", CELL_SIZE, "*");
    }
    printw("\n");
    for (size_t i = 0; i <= this->__matrix_length + 1; i++)
        printw("%*s", CELL_SIZE, "*");
}