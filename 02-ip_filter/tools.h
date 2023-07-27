#pragma once

#include <string>
#include <vector>

namespace tools
{

int version();

std::vector<std::string> split(const std::string &str, char delimiter);

}