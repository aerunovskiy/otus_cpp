#pragma once
#include <boost/algorithm/algorithm.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>

#include "parameters.h"

//------------------------------------------------------------------------

namespace fs_bayan
{

    namespace fs = boost::filesystem;

    //------------------------------------------------------------------------------

    static inline bool check_exception_dir( const fs::path& filePath, const std::vector<std::string>& exceptions_dir )
    {
        return std::any_of( exceptions_dir.begin(), exceptions_dir.end(), [&filePath]( const auto& name ){
            return name == filePath.filename().string(); } );
    }

    //------------------------------------------------------------------------------

    static inline bool check_file_size( const fs::path& filePath, size_t size )
    {
        return fs::file_size(filePath) >= size;
    }

    //------------------------------------------------------------------------------

    static inline  bool check_mask(const fs::path& filePath, const std::vector<std::string>& masks)
    {
        return std::any_of(masks.begin(), masks.end(), [&filePath]( auto& mask )
        {
            auto m = mask;

            boost::algorithm::replace_all(m, ".", "\\.");
            boost::algorithm::replace_all(m, "?", "[^\\\\/]");
            boost::algorithm::replace_all(m, "*", ".*");
            try
            {
                boost::regex pattern(m, boost::regex::icase | boost::regex::ECMAScript);
                return boost::regex_match( filePath.filename().string(), pattern );
            }

            catch( boost::regex_error& e )
            {
                throw std::runtime_error( "Error checking expression : "
                            + filePath.filename().string() + " : " + e.what() );
            }
        });
    }

    //------------------------------------------------------------------------------

    static inline void traverse_dir( const fs::path& directoryPath,
                                     int depth,
                                     std::vector<fs::path>& files,
                                     const Parameters& parameters )
    {
        if (depth < 0)
            return;

        for ( const auto& entry : fs::directory_iterator(directoryPath) )
        {
            if ( fs::is_directory(entry) && !check_exception_dir(entry, parameters.exceptions_dir) )
                traverse_dir( entry.path(), depth - 1, files, parameters );
            else if (fs::is_regular_file( entry ))
            {
                if ( check_mask(entry.path(), parameters.masks)
                    && check_file_size(entry.path(), parameters.min_size) )
                    files.emplace_back(entry);

            }
        }
    }

    //------------------------------------------------------------------------------

    static inline std::vector<fs::path> select_files( const Parameters& parameters )
    {
        try {
            std::vector<fs::path> files;
            for( auto& dir: parameters.dirs )
            {
                if ( !fs::exists(dir) || !fs::is_directory(dir) )
                    throw std::runtime_error( "Invalid directory path: " + dir );

                traverse_dir(dir, parameters.depth, files, parameters );
            }
            return files;

        } catch ( const fs::filesystem_error& ex )
        {
            throw std::runtime_error( std::string( "Filesystem error: " ) + ex.what() );
        }
    }
}
//------------------------------------------------------------------------------
