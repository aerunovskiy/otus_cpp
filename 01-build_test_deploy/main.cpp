#include <iostream>

#include "lib.h"

int main(int, char**)
{
    std::cout << "Version: " << version() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return EXIT_SUCCESS;
}