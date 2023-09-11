
#include <iostream>
#include "sparse_matrix.h"
#include <cassert>

int main (int, char **)
{
    try
    {
        std::cout << "-----------------------" << std::endl;

        SparseMatrix<int, 0> matrix2;

        for(int i = 0; i <= 9;   i++ )
        {
            matrix2[i][i] = i;
            matrix2[i][9-i] = 9-i;
        }

        for (int i = 1; i <= 8; ++i)
        {
            for (int j = 1; j <= 8; ++j)
                std::cout << matrix2[i][j] << ' ';
            std::cout << std::endl;
        }

        std::cout << "-----------------------" << std::endl;


        for(auto& c: matrix2)
        {
            auto [x, y, v] = c;
            std::cout << x << " " << y << " " << v << std::endl;
        }
        std::cout << "-----------------------" << std::endl;

        std::cout << matrix2.size() << std::endl;

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

