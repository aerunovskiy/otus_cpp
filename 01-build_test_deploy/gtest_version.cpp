#include "lib.h"

#include <gtest/gtest.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wweak-vtables"
class test_class : public testing::Test
{};
#pragma GCC diagnostic pop

TEST_F(test_class, test_valid_version)
{
    EXPECT_TRUE(version() > 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}