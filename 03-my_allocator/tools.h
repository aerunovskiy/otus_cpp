#pragma once

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

namespace tools
{

int version();

int factorial(int number);

template <class Allocator>
void fillMap(std::map<int, int, std::less<int>, Allocator>& map) {
    for (int i {0}; i < 10; ++i)
        map.emplace(i, factorial(i));
}

}