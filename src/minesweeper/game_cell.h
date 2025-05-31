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
        inline bool is_flag() const { return this->__is_flag; }
        inline uint8_t num_surrounding_bombs() const { return this->__num_surrounding_bombs; }

    public: /* setters */
        inline void clear() { this->__revealed = 0; this->__is_bomb = 0; this->__is_flag = 0; this->__num_surrounding_bombs = 0; }
        inline void set_revealed() { this->__revealed = true; }
        inline void set_bomb() { this->__is_bomb = true; }
        inline void set_flag(bool is_flag) { this->__is_flag = is_flag; }
        GameCell& operator++(int) { this->__num_surrounding_bombs++; return *this; };

    private:
        bool __revealed;
        bool __is_bomb;
        bool __is_flag;
        uint8_t __num_surrounding_bombs;
};

#endif /* __GAME_CELL_H__ */