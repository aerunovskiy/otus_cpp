#pragma once

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "parameters.h"
#include "select_files.h"

namespace fs = boost::filesystem;

//------------------------------------------------------------------------------

class Bayan
{
public:

    friend class Builder;

    class File
    {
    public:
        File(fs::path p, int i)
        {
            path = std::move(p);
            id = i;
        }

        std::vector<std::string> blocks;
        fs::path path;
        size_t id;
        bool completed = false;

        bool operator==(const File& other) const {
            return blocks == other.blocks;
        }

        bool operator!=(const File& other) const {
            return blocks != other.blocks;
        }

    };

    void run();


private:

    bool _add_hash_block(File& f, size_t ind);

    bool _compare(File& first, File& second);

    Parameters _parameters;

    std::unique_ptr<HashBayan> _hash;
};

//------------------------------------------------------------------------------

class Builder
{
public:
    Builder();

    ~Builder() = default;

    void print_parameters();

    Builder& set_depth( int level );

    Builder& set_min_size( int min_size );

    Builder& set_block_size( int block_size );

    Builder& set_hash_type( const std::string& hash_type );

    Builder& set_dirs( const std::vector<std::string>& dirs );

    Builder& set_dir_exceptions( const std::vector<std::string>& dirs );

    Builder& set_masks( const std::vector<std::string>& masks );

    Builder& set_parameters( const Parameters& params );

    std::shared_ptr<Bayan> build_shared();

private:

    std::shared_ptr<Bayan> _bayan;
};

//------------------------------------------------------------------------------