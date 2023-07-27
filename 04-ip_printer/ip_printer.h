/*!
 * \file ip_printer.h
 * \brief Functions for IP print
 * \author Alexey Erunovskiy
 */
#pragma once

#include <list>
#include <tuple>
#include <type_traits>
#include <vector>

/*!
 * \namespace task
 * \brief For template functions
 */
namespace task
{

/*!
 * \brief Template function version for string
 * \param [in] str IP (string version)
 */
template<typename StringT,
         typename = std::enable_if_t<std::is_same_v<StringT, std::string>>>
auto print_ip(const StringT &str) {
    std::cout << str << std::endl;
}

/*!
 * \brief Template function version for integers
 * \param [in] _int IP (integer version)
 */
template<typename T,
         typename = std::enable_if_t<std::numeric_limits<T>::is_integer>>
void print_ip (T _int) {
    auto size = sizeof(_int);
    auto p = (uint8_t *) &_int + size - 1;

    for (size_t i {0}; i < size - 1; ++i, --p) {
        std::cout << (int) *p << '.';
    }
    std::cout << (int) *p << std::endl;
}

/*!
 * \brief Template function version for container
 * \param [in] container IP (container version)
 */
template<typename ContainerT,
         typename = std::enable_if_t<std::is_same_v<ContainerT, std::vector<typename ContainerT::value_type>> ||
                                     std::is_same_v<ContainerT, std::list<typename ContainerT::value_type>>>>
void print_ip(const ContainerT& container) {
    auto it = container.begin();

    for (size_t i {0}; i < container.size() - 1; ++i, ++it)
        std::cout << *it << '.';

    std::cout << *it << std::endl;
}


/*!
 * \brief Template function for tuple print
 * \param [in] tuple IP
 */
template<typename TupleT, size_t ...Idx>
void print_tuple(const TupleT& tuple, std::index_sequence<Idx...>) {
    size_t index {0};

    auto print_element = [&index] (const auto x) {
        std::enable_if_t<std::is_same_v<std::tuple_element_t<0, TupleT>, std::remove_const_t<decltype(x)>>, int> var;
        (void) var;

        if(index++ > 0)
            std::cout << ".";

        std::cout << x;
    };

    (print_element(std::get<Idx>(tuple)), ...);
}

/*!
 * \brief Template function version for tuple
 * \param [in] tuple IP (tuple version)
 */
template<typename ...T>
void print_ip(const std::tuple<T...>& tuple) {
    print_tuple(tuple, std::make_index_sequence<std::tuple_size<std::tuple<T...>>::value>{});
}

}