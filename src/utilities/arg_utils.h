#ifndef __UTILITIES_ARGUMENTS_H__
#define __UTILITIES_ARGUMENTS_H__

#include <string>
#include <string.h>
#include <cstdint>

void print_help_argument(const char* argument, const char* description);
uint32_t get_numerical_argument(std::string& arg_str, const size_t arg_length);
void parse_args(std::string arg);

#endif /* __UTILITIES_ARGUMENTS_H__ */