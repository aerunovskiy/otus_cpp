#pragma once

#include <algorithm>

#include "ip.h"

namespace filters
{

void filter_1(const std::vector<Ip>& ip_pool, std::vector<Ip>& filtered_ip) {
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filtered_ip), [](const Ip& ip) {
        return ip.octets[0] == 1;
    });
}

void filter_46_70(const std::vector<Ip>& ip_pool, std::vector<Ip>& filtered_ip) {
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filtered_ip), [](const Ip& ip) {
        return ip.octets[0] == 46 && ip.octets[1] == 70;
    });
}

void filter_46(const std::vector<Ip>& ip_pool, std::vector<Ip>& filtered_ip) {
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filtered_ip), [](const Ip& ip) {
        return std::any_of(ip.octets.cbegin(), ip.octets.cend(), [](int octet){
           return octet == 46;
        });
    });
}

}