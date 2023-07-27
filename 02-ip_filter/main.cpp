#include <algorithm>
#include <iostream>

#include "ip.h"
#include "filters.h"
#include "tools.h"

int main(int, char**) {
    try {
        std::vector<Ip> ip_pool {};

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = tools::split(line, '\t');
            Ip ip {};
            ip.initialize(tools::split(v.at(0), '.'));
            ip_pool.emplace_back(ip);
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](const Ip& lhs, const Ip& rhs) {
           return lhs > rhs;
        });

        for(const auto& ip : ip_pool)
            ip.print();

        std::vector<Ip> filtered_ip {};

        filters::filter_1(ip_pool, filtered_ip);

        for(const auto& ip : filtered_ip)
            ip.print();

        filtered_ip.clear();

        filters::filter_46_70(ip_pool, filtered_ip);

        for(const auto& ip : filtered_ip)
            ip.print();

        filtered_ip.clear();

        filters::filter_46(ip_pool, filtered_ip);

        for(const auto& ip : filtered_ip)
            ip.print();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}