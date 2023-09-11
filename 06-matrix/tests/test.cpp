#include "gtest/gtest.h"

#include "../src/sparse_matrix.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST( test_matrix, test_matrix )
{
    SparseMatrix<int, -1> matrix;
    ASSERT_EQ(matrix.size(), 0);

    auto a = matrix[0][0];

    ASSERT_EQ(a, -1);

    ASSERT_EQ(matrix.size(), 0);

    matrix[100][100] = 314;

    ASSERT_EQ(matrix[100][100], 314);

    ASSERT_EQ(matrix.size(), 1);

    matrix[200][200] = 3;

    matrix[200][200] = -1;

    ASSERT_EQ(matrix.size(), 2);

    for(auto& c: matrix)
    {
        auto [x, y, v] = c;
        std::cout << x << " " << y << " " << v << std::endl;
    }

}