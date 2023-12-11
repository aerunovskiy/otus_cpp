#include <fstream>

#include "gtest/gtest.h"

#include "../src/select_files.h"

namespace fs = boost::filesystem;


TEST(test_files, test)
{
    Parameters parameters;
    parameters.min_size = 0;
    parameters.dirs = {"../tests/test_directory"};
    parameters.masks = {"*.txt"};
    parameters.depth = 0;

    auto result1 = fs_bayan::select_files(parameters);
    auto true_result1 = std::vector<fs::path>{"../tests/test_directory/12.txt",
                                              "../tests/test_directory/empty.txt"};
    ASSERT_EQ(result1, true_result1);

    parameters.masks = {"empty.*"};
    auto result2 = fs_bayan::select_files(parameters);
    auto true_result2 = std::vector<fs::path>{"../tests/test_directory/empty.txt",
                                              "../tests/test_directory/empty.cmake"};
    ASSERT_EQ(result2, true_result2);

    parameters.masks = {"?.txt"};
    parameters.depth = 2;
    auto result3 = fs_bayan::select_files(parameters);
    auto true_result3 = std::vector<fs::path>{"../tests/test_directory/depth1/1.txt"};
    ASSERT_EQ(result3, true_result3);

    parameters.masks = {"1?.txt"};
    auto result4 = fs_bayan::select_files(parameters);
    auto true_result4 = std::vector<fs::path>{ "../tests/test_directory/12.txt"};
    ASSERT_EQ(result4, true_result4);

    parameters.masks = {"1*.txt"};
    parameters.depth = 4;
    auto result5 = fs_bayan::select_files(parameters);
    auto true_result5 = std::vector<fs::path>{ "../tests/test_directory/12.txt",
                                              "../tests/test_directory/depth1/1.txt" ,
                                               "../tests/test_directory/depth1/1CMakeLists.txt"
                                               };
    ASSERT_EQ(result5, true_result5);

    parameters.min_size = 1;
    parameters.dirs = {"../wrong"};

    ASSERT_ANY_THROW(fs_bayan::select_files(parameters););

    parameters.dirs = {"../tests/test_directory"};
    parameters.masks = {"*.txt"};
    parameters.depth = 0;

    auto result6 = fs_bayan::select_files(parameters);
    auto true_result6 = std::vector<fs::path>{"../tests/test_directory/12.txt"};
    ASSERT_EQ(result6, true_result6);

    parameters.masks = {"1*.txt"};
    parameters.depth = 4;
    parameters.exceptions_dir = {"depth1"};
    auto result7 = fs_bayan::select_files(parameters);
    auto true_result7 = std::vector<fs::path>{"../tests/test_directory/12.txt"};
    ASSERT_EQ(result7, true_result7);

}
