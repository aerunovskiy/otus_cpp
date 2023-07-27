#pragma once

#include <array>
#include <iostream>
#include <cstdint>
#include <tuple>
#include <vector>

struct Ip
{
    static const size_t OCTETS_NUMBER { 4 };

    explicit Ip()
    : octets()
    {}

    void initialize(const std::vector<std::string>& str) {
        if (str.size() != 4) {
            throw std::invalid_argument("IP must contain four octets");
        }

        for (size_t i { 0 }; i < OCTETS_NUMBER; ++i) {
            if (std::stoi(str[i]) < 0 || std::stoi(str[i]) > 255)
                throw std::invalid_argument("Octet = " + str[i] + " but it must be from 0 to 255");

            try {
                octets[i] = std::stoi(str[i]);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    };

    std::array<int, OCTETS_NUMBER> octets;

    void print() const {
        for (size_t i { 0 }; i < OCTETS_NUMBER - 1; ++i)
            std::cout << octets[i] << '.';

        std::cout << octets[OCTETS_NUMBER - 1] << '\n';
    }

    bool operator > (const Ip& ip) const {
        return octets > ip.octets;
    }

    bool operator == (const Ip& ip) const {
        return octets == ip.octets;
    }
};