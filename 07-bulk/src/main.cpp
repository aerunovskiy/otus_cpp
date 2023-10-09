
#include <iostream>
#include <cassert>

int main (int, char **)
{
    try
    {

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

