#include <gtest/gtest.h>

#include "ip.h"
#include "filters.h"
#include "tools.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wweak-vtables"
class test_class : public testing::Test
{
public:
    std::vector<std::string> ip_list {
        "2.3.4.5",
        "1.2.3.4",
        "1.3.4.5",
        "111.30.40.50",
        "1.30.40.50",
        "11.46.70.50",
        "46.70.70.46",
        "46.70.1.2",
        "0.46.0.0",
        "70.46.0.0",
        "46.70.13.31"
    };

    std::vector<std::string> ip_sorted {
        "111.30.40.50",
        "70.46.0.0",
        "46.70.70.46",
        "46.70.13.31",
        "46.70.1.2",
        "11.46.70.50",
        "2.3.4.5",
        "1.30.40.50",
        "1.3.4.5",
        "1.2.3.4",
        "0.46.0.0"
    };
};
#pragma GCC diagnostic pop

TEST_F(test_class, test_valid_version)
{
    EXPECT_TRUE(tools::version() > 0);
}

TEST_F(test_class, test_ip_sort)
{
    std::vector<Ip> ip_pool;

    for (const auto& ip_str : ip_list)
    {
        Ip ip{};
        ip.initialize(tools::split(ip_str, '.'));
        ip_pool.emplace_back(ip);
    }

    std::sort(ip_pool.begin(), ip_pool.end(), [](const Ip& lhs, const Ip& rhs) {
        return lhs > rhs;
    });

    for(size_t i {0}; i < ip_pool.size() - 1; ++i)
        EXPECT_TRUE(ip_pool.at(i) > ip_pool.at(i + 1));
}

TEST_F(test_class, test_filter_1)
{
    std::vector<Ip> ip_pool {};
    std::vector<Ip> filtered_ip {};
    std::vector<Ip> filter_sample {3, Ip()};

    filter_sample[0].initialize(tools::split("1.30.40.50", '.'));
    filter_sample[1].initialize(tools::split("1.3.4.5", '.'));
    filter_sample[2].initialize(tools::split("1.2.3.4", '.'));

    for (const auto& ip_str : ip_list)
    {
        Ip ip{};
        ip.initialize(tools::split(ip_str, '.'));
        ip_pool.emplace_back(ip);
    }

    std::sort(ip_pool.begin(), ip_pool.end(), [](const Ip& lhs, const Ip& rhs) {
        return lhs > rhs;
    });

    filters::filter_1(ip_pool, filtered_ip);

    ASSERT_TRUE(filtered_ip.size() == filter_sample.size());

    for (size_t i {0}; i < filtered_ip.size(); ++i)
        EXPECT_TRUE(filtered_ip.at(i) == filter_sample.at(i));
}

TEST_F(test_class, test_filter_46_70)
{
    std::vector<Ip> ip_pool {};
    std::vector<Ip> filtered_ip {};
    std::vector<Ip> filter_sample {3, Ip()};

    filter_sample[0].initialize(tools::split("46.70.70.46", '.'));
    filter_sample[1].initialize(tools::split("46.70.13.31", '.'));
    filter_sample[2].initialize(tools::split("46.70.1.2", '.'));

    for (const auto& ip_str : ip_list)
    {
        Ip ip{};
        ip.initialize(tools::split(ip_str, '.'));
        ip_pool.emplace_back(ip);
    }

    std::sort(ip_pool.begin(), ip_pool.end(), [](const Ip& lhs, const Ip& rhs) {
        return lhs > rhs;
    });

    filters::filter_46_70(ip_pool, filtered_ip);

    ASSERT_TRUE(filtered_ip.size() == filter_sample.size());

    for (size_t i {0}; i < filtered_ip.size(); ++i)
        EXPECT_TRUE(filtered_ip.at(i) == filter_sample.at(i));
}

TEST_F(test_class, test_filter_46)
{
    std::vector<Ip> ip_pool {};
    std::vector<Ip> filtered_ip {};
    std::vector<Ip> filter_sample {6, Ip()};

    filter_sample[0].initialize(tools::split("70.46.0.0", '.'));
    filter_sample[1].initialize(tools::split("46.70.70.46", '.'));
    filter_sample[2].initialize(tools::split("46.70.13.31", '.'));
    filter_sample[3].initialize(tools::split("46.70.1.2", '.'));
    filter_sample[4].initialize(tools::split("11.46.70.50", '.'));
    filter_sample[5].initialize(tools::split("0.46.0.0", '.'));

    for (const auto& ip_str : ip_list)
    {
        Ip ip{};
        ip.initialize(tools::split(ip_str, '.'));
        ip_pool.emplace_back(ip);
    }

    std::sort(ip_pool.begin(), ip_pool.end(), [](const Ip& lhs, const Ip& rhs) {
        return lhs > rhs;
    });

    filters::filter_46(ip_pool, filtered_ip);

    ASSERT_TRUE(filtered_ip.size() == filter_sample.size());

    for (size_t i {0}; i < filtered_ip.size(); ++i)
        EXPECT_TRUE(filtered_ip.at(i) == filter_sample.at(i));
}

TEST_F(test_class, test_init)
{
    Ip ip {};

    ASSERT_NO_THROW(
        ip.initialize(tools::split("70.46.0.0", '.'))
    );
}

TEST_F(test_class, test_init_extra_octet)
{
    Ip ip {};

    ASSERT_THROW(
        ip.initialize(tools::split("70.46.0.0.1", '.')), std::invalid_argument
    );
}

TEST_F(test_class, test_init_big_octet)
{
    Ip ip {};

    ASSERT_THROW(
        ip.initialize(tools::split("300.400.500.600", '.')), std::invalid_argument
    );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}