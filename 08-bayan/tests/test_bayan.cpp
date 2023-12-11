#include <fstream>
#include "gtest/gtest.h"

#include "../src/hash.h"
#include "../src/bayan.h"

template<typename F>
std::string record_out_stream_buffer(F&& f)
{
    std::stringstream buffer;

    std::streambuf *sbuf = std::cout.rdbuf();

    std::cout.rdbuf(buffer.rdbuf());

    f->run();

    std::cout.rdbuf(sbuf);

    std::string result = buffer.str();

    return result;
}


TEST(test_bayan, test_hash)
{
    Parameters parameters;
    parameters.min_size = 0;
    parameters.dirs = {"../tests/test_directory"};
    parameters.masks = {"*.cpp"};
    parameters.depth = 4;
    parameters.block_size = 100;

    Builder builder;
    builder.set_parameters(parameters);
    auto bayan_md5 = builder.set_hash_type("md5").build_shared();

    auto bayan_crc32 =  builder.set_hash_type("crc32").build_shared();

    ASSERT_EQ(record_out_stream_buffer(bayan_crc32), record_out_stream_buffer(bayan_md5) );

}