#pragma once

#include <unordered_map>
//#include <numeric>

template<class Type, Type DEFAULT_VALUE>
class SparseMatrix
{
public:
    SparseMatrix() = default;

    void operator[](size_t pos)
    {
        return matrix_.at(pos);
    }

private:
    std::unordered_map<std::pair<size_t, size_t>, std::shared_ptr<Type>> matrix_;
};