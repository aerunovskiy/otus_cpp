#pragma once
#include <iostream>

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

namespace hash_bayan
{
    enum class HashType
    {
        CRC32,
        MD5,
    };

    inline hash_bayan::HashType hash_from_string(const std::string& type)
    {
        auto hash_type = type;
        static const std::unordered_map<std::string, hash_bayan::HashType> string_hash =
                {
                        { "CRC32", hash_bayan::HashType::CRC32 },
                        { "MD5",   hash_bayan::HashType::MD5 }
                };

        std::transform(hash_type.begin(), hash_type.end(), hash_type.begin(),
                       [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

        if (auto it = string_hash.find(hash_type); it != string_hash.end())
            return it->second;
        else
            throw std::runtime_error("hash type " + type + " not found");
    }

    inline std::string hash_2_string(hash_bayan::HashType hash_type)
    {
        switch (hash_type)
        {
            case hash_bayan::HashType::CRC32:   return "CRC32";
            case hash_bayan::HashType::MD5:	    return "MD5";
            default:                            throw std::runtime_error("unknown hash_type");
        }
    }
}

//------------------------------------------------------------------------------

class HashBayan
{
public:
    HashBayan() = default;

    virtual ~HashBayan(){};

    virtual std::string apply(const std::string& input) = 0;

    virtual hash_bayan::HashType type() = 0;
};

//------------------------------------------------------------------------------

class HashCRC32 : public HashBayan
{
public:
    HashCRC32() = default;
    ~HashCRC32() = default;
    std::string apply(const std::string& input) override
    {
        boost::crc_32_type crc_32;
        crc_32.process_bytes(input.data(), input.size());
        return std::to_string(crc_32.checksum());
    }

    hash_bayan::HashType type() override
    {
        return hash_bayan::HashType::CRC32;
    }

};

//------------------------------------------------------------------------------

class HashMD5 : public HashBayan
{
public:
    HashMD5() = default;
    ~HashMD5() = default;
    std::string apply(const std::string& input) override
    {

        boost::uuids::detail::md5::digest_type digest;
        boost::uuids::detail::md5 md5;
        md5.process_bytes(input.data(), input.size());
        md5.get_digest(digest);
        const auto charDigest = reinterpret_cast<const char *>(&digest);
        std::string result;
        boost::algorithm::hex(charDigest, charDigest + (sizeof(boost::uuids::detail::md5::digest_type)/sizeof(int)), std::back_inserter(result));
        return result;

    }
    hash_bayan::HashType type() override
    {
        return hash_bayan::HashType::MD5;
    }

};

//------------------------------------------------------------------------------