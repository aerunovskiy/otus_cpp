#include <algorithm>
#include <iostream>

#include "allocator.h"
#include "list.h"
#include "tools.h"

int main(int, char**) {
    try {
        std::cout << "1. Fill and print usual map:\n" << std::endl;
        std::map<int, int> factorials_map;
        tools::fillMap(factorials_map);
        for (const auto& factorial : factorials_map)
            std::cout << factorial.first << ' ' << factorial.second << std::endl;

        std::cout << "\n2. Fill and print map with allocator:\n" << std::endl;
        std::map<int, int, std::less<int>, Allocator<std::pair<int, int>, 10>> allocated_factorials_map;
        tools::fillMap(allocated_factorials_map);
        for (const auto& factorial : allocated_factorials_map)
            std::cout << factorial.first << ' ' << factorial.second << std::endl;

        std::cout << "\n3. Fill and print list:\n" << std::endl;
        List<int> list;
        for (int i {0}; i < 10; ++i) {
            list.push_back(i);
        }
        list.print();

        std::cout << "\n4. Fill and print list with allocator:\n" << std::endl;
        List<int, Allocator<int, 10>> allocated_list;
        for (int i {0}; i < 10; ++i) {
            allocated_list.push_back(i);
        }
        list.print();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}