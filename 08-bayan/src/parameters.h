#pragma once
#include "hash.h"
#include <vector>
#include <string>

struct Parameters
{
    std::vector<std::string> dirs;
    std::vector<std::string> exceptions_dir;
    std::vector<std::string> masks;
    int min_size;
    int depth;
    int block_size;
};
