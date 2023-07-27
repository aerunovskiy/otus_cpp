/*!
 * \file main.cpp
 * \brief Entry app file
 *
 * \author Alexey Erunovskiy
 * \date May 2023
 */

#include <cassert>
#include <iostream>
#include <tuple>

#include "sparse_matrix.h"

/*!
 * \brief Entry point
 *
 * Execution of the program starts here.
 *
 * \param[in] argc Number of arguments.
 * \param[in] argv List of arguments.
 *
 * \return App exit status.
 */
int main(int, char**)
{
// бесконечная матрица int заполнена значениями -1
    SparseMatrix<int, -1> matrix;
//    assert(matrix.size() == 0); // все ячейки свободны
//    auto a = matrix[0][0];
//    assert(a == -1);
//    assert(matrix.size() == 0);
//    matrix[100][100] = 314;
//    assert(matrix[100][100] == 314);
//    assert(matrix.size() == 1);
//// выведется одна строка
//// 100100314
//    for(auto c : matrix)
//    {
//        int x;
//        int y;
//        int v;
//        std::tie(x, y, v) = c;
//        std::cout << x << y << v << std::endl;
//    }

    return EXIT_SUCCESS;
}