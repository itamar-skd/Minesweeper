#ifndef __MINESWEEPER_CONFIG_H__
#define __MINESWEEPER_CONFIG_H__

#include <cstdlib>

/**
 * @brief singleton container for game settings, such as matrix size and number of minefields.
 */
class Config
{
    private:
        Config() = default;
        ~Config() = default;

    public:
        Config(Config const &) = delete;
        Config& operator=(Config const &) = delete;

    public: /* singleton initialization */
        Config& config();
        void init(size_t matrix_length, size_t matrix_width, size_t num_minefields);

    public: /* getters */
        inline size_t matrix_length() { return this->__matrix_length; }
        inline size_t matrix_width() { return this->__matrix_width; }
        inline size_t num_minefields() { return this->__num_minefields; }

    private:
        size_t __matrix_length;
        size_t __matrix_width;
        size_t __num_minefields;

} /* class Config */;

#endif /* __MINESWEEPER_CONFIG_H__ */