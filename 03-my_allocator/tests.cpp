#include <gtest/gtest.h>

#include "list.h"
#include "tools.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wweak-vtables"
class test_class : public testing::Test
{};
#pragma GCC diagnostic pop

TEST_F(test_class, test_valid_version)
{
    EXPECT_TRUE(tools::version() > 0);
}

TEST_F(test_class, push_back_test) {
    List<int> list;
    list.push_back(1);
    EXPECT_EQ(1, list[0]->data);
    EXPECT_EQ(1, list.size());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}