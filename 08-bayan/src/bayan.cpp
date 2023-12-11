#include "bayan.h"

bool Bayan::_add_hash_block(File& f, size_t ind)
{
    if(f.blocks.size() <= ind)
    {
        std::ifstream file(f.path, std::ios::binary);
        if (!file)
            throw std::runtime_error( "error opening file!");

        file.seekg(f.blocks.size() * _parameters.block_size, std::ios::beg);

        std::string buffer(_parameters.block_size, '\0');
        file.read(&buffer[0], _parameters.block_size);
        f.blocks.emplace_back(_hash->apply(buffer));

        if (file.tellg() == std::ifstream::pos_type(-1))
        {
            f.completed = true;
            return false;
        }
    }
    return true;
}


bool Bayan::_compare(File& first, File& second)
{
    bool ok = true;
    int i = 0;
    while(ok)
    {
        bool ok1 = _add_hash_block(first, i);
        bool ok2 = _add_hash_block(second, i);

        ok = ok1 && ok2;
        if (first.blocks.at(i) != second.blocks.at(i))
            return false;
        i++;
    }
    return first.completed && second.completed;
}


void Bayan::run()
{
    std::vector<fs::path> files = fs_bayan::select_files( _parameters );
    std::unordered_map<int, std::set<int>> duplicates;
    std::vector<File> scan_files;

    if (files.size() > 1)
    {
        for(size_t i = 0; i < files.size(); ++i)
        {
            scan_files.emplace_back(files.at(i), i);
            std::cout << files.at(i).filename().string() << std::endl;
        }


        for(size_t i = 0; i < scan_files.size() - 1; ++i)
        {
            for(size_t j = i + 1; j < scan_files.size(); ++j)
            {
                auto& first = scan_files.at(i);
                auto& second = scan_files.at(j);
                if( first.id == second.id )
                    continue;
                if (_compare(first, second))
                {
                    auto [it, ok] = duplicates.emplace(first.id, std::set<int>());
                    it->second.emplace(second.id);
                    second.id = first.id;
                }

            }

        }
    }

    std::cout << "Results of scanning: " << std::endl;
    std::cout << std::endl;
    for(auto & duplicate :duplicates)
    {
        std::cout << scan_files.at(duplicate.first).path << std::endl;
        for(auto & d :duplicate.second)
            std::cout << scan_files.at(d).path << std::endl;

        std::cout << std::endl;
    }
    if(duplicates.empty())
        std::cout << "No duplicates found" << std::endl;

}

Builder::Builder()
{
    _bayan = std::make_shared<Bayan>();
}

void Builder::print_parameters()
{
    std::cout << "------------ Parameters ---------------" << std::endl;

    std::cout << "Directories: ";
    for(const auto& d: _bayan->_parameters.dirs )
        std::cout << d << " " ;
    std::cout << std::endl;

    std::cout << "Directories exceptions: ";
    for(const auto& d: _bayan->_parameters.exceptions_dir )
        std::cout << d << " " ;
    std::cout << std::endl;

    std::cout << "Masks: ";
    for(const auto& m: _bayan->_parameters.masks )
        std::cout << m << " " ;
    std::cout << std::endl;

    std::cout << "Min file size: " << _bayan->_parameters.min_size << std::endl;

    std::cout << "Deep depth size: " << _bayan->_parameters.depth << std::endl;

    std::cout << "Block size: " << _bayan->_parameters.block_size << std::endl;

    std::cout << "Hash: " << hash_2_string(_bayan->_hash->type()) << std::endl;

}

Builder& Builder::set_depth( int level )
{
    _bayan->_parameters.depth = level;
    return *this;
}

Builder& Builder::set_min_size( int min_size )
{
    _bayan->_parameters.min_size = min_size;
    return *this;
}

Builder& Builder::set_block_size( int block_size )
{
    _bayan->_parameters.block_size = block_size;
    return *this;
}


Builder& Builder::set_hash_type( const std::string& hash_type )
{
    auto type = hash_bayan::hash_from_string(hash_type);

    switch(type)
    {
        case(hash_bayan::HashType::CRC32):
        {
            _bayan->_hash = std::make_unique<HashCRC32>();
            break;
        }
        case(hash_bayan::HashType::MD5):
        {
            _bayan->_hash = std::make_unique<HashMD5>();
            break;
        }
    }

    return *this;
}


Builder& Builder::set_dirs( const std::vector<std::string>& dirs )
{
    _bayan->_parameters.dirs = dirs;
    return *this;
}


Builder& Builder::set_dir_exceptions( const std::vector<std::string>& dirs )
{
    _bayan->_parameters.exceptions_dir = dirs;
    return *this;
}


Builder& Builder::set_masks( const std::vector<std::string>& masks)
{
    _bayan->_parameters.masks = masks;
    return *this;
}

Builder& Builder::set_parameters( const Parameters& params )
{
    _bayan->_parameters = params;
    return *this;
}

//!>
std::shared_ptr<Bayan> Builder::build_shared()
{
    print_parameters();
    return _bayan;
}

