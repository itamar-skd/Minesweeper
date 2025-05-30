#include "config.h"

Config& Config::config()
{
    static Config _config;
    return _config;
}

void Config::init(size_t matrix_length, size_t matrix_width, size_t num_minefields)
{
    this->__matrix_length = matrix_length;
    this->__matrix_width = matrix_width;
    this->__num_minefields = num_minefields;
}