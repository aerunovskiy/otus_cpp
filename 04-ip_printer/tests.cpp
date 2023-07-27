/*!
 * \file tests.cpp
 * \brief Test file
 * \author Alexey Erunovskiy
 */

#include <gtest/gtest.h>

#include "ip_printer.h"
#include "tools.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wweak-vtables"
class test_class : public testing::Test
{};
#pragma GCC diagnostic pop

/*!
 * \brief Application version test
 */
TEST_F(test_class, test_valid_version) {
    EXPECT_TRUE(tools::version() > 0);
}