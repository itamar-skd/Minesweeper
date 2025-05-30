#ifndef __GAME_CELL_H__
#define __GAME_CELL_H__

#include <cstdint>

class GameCell
{
    public:
        GameCell() = default;
        ~GameCell() = default;

    public: /* getters */
        inline bool revealed() const { return this->__revealed; }
        inline bool is_bomb() const { return this->__is_bomb; }
        inline uint8_t num_surrounding_bombs() const { return this->__num_surrounding_bombs; }

    public: /* setters */
        inline void set_revealed() { this->__revealed = true; }
        inline void set_bomb() { this->__is_bomb = true; }
        GameCell& operator++(int) { this->__num_surrounding_bombs++; return *this; };

    private:
        bool __revealed;
        bool __is_bomb;
        uint8_t __num_surrounding_bombs;
};

#endif /* __GAME_CELL_H__ */