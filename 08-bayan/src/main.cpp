#include <boost/program_options.hpp>
#include <iostream>

#include "bayan.h"

namespace po = boost::program_options;
int main (int argc, char** argv)
{
    try
    {
        int depth;
        int min_size;
        int block_size;
        std::string hash_type;

        po::options_description desc("options");

        desc.add_options()
                ("help", "produce help message")
                ("dirs,d", po::value<std::vector<std::string>>()->multitoken()->composing(), "directories to scan")
                ("dirs_except, de", po::value<std::vector<std::string>>()->multitoken()->composing(), "directories to exclude from scanning")
                ("depth", po::value<int>(&depth)->default_value(0), "directories depth of scannig")
                ("min_size", po::value<int>(&min_size)->default_value(1), "min size of filw")
                ("masks", po::value<std::vector<std::string>>()->multitoken()->composing(),  "name masks allowed for comparison")
                ("S", po::value<int>(&block_size)->default_value(100), "block size")
                ("H", po::value<std::string>(&hash_type)->default_value("md5"), "hash algorithm : crc32, md5 ");

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
        po::notify(vm);

        Builder bayan_builder;

        if ( vm.count("dirs") )
        {
            std::vector<std::string> dirs = vm["dirs"].as<std::vector<std::string>>();
            bayan_builder.set_dirs(dirs);
        }

        if ( vm.count("dirs_except") )
        {
            std::vector<std::string> dirs_except = vm["dirs_except"].as<std::vector<std::string>>();
            bayan_builder.set_dir_exceptions(dirs_except);
        }

        if ( vm.count("masks") )
        {
            std::vector<std::string> masks = vm["masks"].as<std::vector<std::string>>();
            bayan_builder.set_masks(masks);
        }

        if ( vm.count("help") )
        {
            std::cout << desc << std::endl;
            return 0;
        }

        if ( vm.count("depth") )
            bayan_builder.set_depth( depth );

        if ( vm.count("min_size") )
            bayan_builder.set_min_size( min_size );

        if ( vm.count("S") )
            bayan_builder.set_block_size( block_size );

        if ( vm.count("H") )
            bayan_builder.set_hash_type( hash_type );

        auto bayan = bayan_builder.build_shared();

        bayan->run();
    }
    catch( const std::exception &e )
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

