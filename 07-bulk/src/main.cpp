#include <cassert>

#include "bulk.hpp"

int main (int argc, char ** argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong arguments number!" << std::endl;

        return EXIT_FAILURE;
    }

    auto cmd_number = atoi(argv[1]);

    std::string cmd;

    try
    {
        Bulk bulk(cmd_number);

        while (cmd != "EOF")
        {
            std::cin >> cmd;

            bulk.push_back(cmd);
        }

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

