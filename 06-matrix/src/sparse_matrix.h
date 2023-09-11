#pragma once

#include <vector>
#include <map>
#include <optional>
#include <memory>

template<typename T, T V_DEFAULT>
class SparseMatrix
{
private:

    class MatrixValue;
    class iterator;
    class MatrixRow;

    // DOK — Dictionary of Keys
    std::map<std::pair<size_t, size_t>, T> _values;

public:

    SparseMatrix() = default;

    SparseMatrix(size_t rows, size_t cols, const T& value = V_DEFAULT);

    ~SparseMatrix() = default;

    void clear();

    size_t size() const;

    bool empty() const;

    std::optional<T> find( size_t row, size_t col );

    void set( size_t row, size_t col, const T& value);

    const T& operator() ( size_t row, size_t col );

    MatrixRow operator[](size_t row);

    iterator begin();

    iterator end();

};

template<typename T, T V_DEFAULT>
SparseMatrix<T, V_DEFAULT>::SparseMatrix(size_t rows, size_t cols, const T& value)
{
    for(size_t i = 0; i < rows; ++i)
        for(size_t j = 0; j < cols; ++j)
            set(i, j, value);
}

template<typename T, T V_DEFAULT>
void SparseMatrix<T, V_DEFAULT>::set( size_t row, size_t col, const T& value)
{
    _values.emplace(std::make_pair(row ,col), value);
}

template<typename T, T V_DEFAULT>
void SparseMatrix<T, V_DEFAULT>::clear()
{
    _values.clear();
}

template<typename T, T V_DEFAULT>
size_t SparseMatrix<T, V_DEFAULT>::size() const
{
    return _values.size();
}

template<typename T, T V_DEFAULT>
bool SparseMatrix<T, V_DEFAULT>::empty() const
{
    return _values.empty();
}

template<typename T, T V_DEFAULT>
std::optional<T> SparseMatrix<T, V_DEFAULT>::find( size_t row, size_t col )
{
    if (auto it = _values.find(std::make_pair(row ,col)); it != _values.end())
        return _values.at(std::make_pair(row ,col));
    else
        return {};
}

template<typename T, T V_DEFAULT>
const T& SparseMatrix<T, V_DEFAULT>::operator()( size_t row, size_t col )
{
    return find(row, col).value_or(V_DEFAULT);
}

template<typename T, T V_DEFAULT>
typename SparseMatrix<T, V_DEFAULT>::MatrixRow SparseMatrix<T, V_DEFAULT>::operator[](size_t row)
{
    return MatrixRow(*this, row);
}

template<typename T, T V_DEFAULT>
typename SparseMatrix<T, V_DEFAULT>::iterator SparseMatrix<T, V_DEFAULT>::begin()
{
    return iterator(_values.begin());
}

template<typename T, T V_DEFAULT>
typename SparseMatrix<T, V_DEFAULT>::iterator SparseMatrix<T, V_DEFAULT>::end()
{
    return iterator( _values.end());
}


template<typename T, T V_DEFAULT>
class SparseMatrix<T, V_DEFAULT>::MatrixRow
{
    friend class SparseMatrix;
public:

    template<typename U>
    MatrixRow& operator=(U&& val)
    {
        if (val != V_DEFAULT)
        {
            auto [ it, ok] =  _base._values.emplace(std::make_pair(_row , _col_current), V_DEFAULT);
            (*it).second = val;
        }
        return *this;
    }

    operator T() const
    {
        return _base.find(_row, _col_current).value_or(V_DEFAULT);
    }

    const MatrixRow& operator[](size_t col) const
    {
        return _base.find(_row, col).value_or(V_DEFAULT);
    }

    MatrixRow& operator[](size_t col)
    {
        _col_current = col;
        return *this ;
    }

private:
    MatrixRow(SparseMatrix &parent, size_t row) :
            _base(parent),
            _row(row)
    {}

    SparseMatrix& _base;
    size_t _row;
    size_t _col_current;
};



template<typename T, T value_default>
class SparseMatrix<T, value_default>::MatrixValue
{
public:

    MatrixValue(const std::pair<const std::pair<size_t, size_t>, T>& v)
    {
        row = v.first.first;
        col = v.first.second;
        value = v.second;
    }

    MatrixValue& operator=(const std::pair<const std::pair<size_t, size_t>, T>& v)
    {
        row = v.first.first;
        col = v.first.second;
        value = v.second;
        return *this;
    }

    MatrixValue(const MatrixValue& other)
    {
        row = other.row;
        col = other.col;
        value = other.value;
    }

    MatrixValue& operator=(const MatrixValue& other)
    {
        row = other.row;
        col = other.col;
        value = other.value;
        return *this;
    }
    MatrixValue(MatrixValue&&)= delete;
    MatrixValue& operator=(MatrixValue&&) = delete;

    size_t row;
    size_t col;
    T value;
};


template<typename T, T value_default>
class SparseMatrix<T, value_default>::iterator
{
public:

    using value_type = MatrixValue;
    using reference = value_type& ;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    using container = std::map<std::pair<size_t, size_t>, T>;

    iterator( typename container::iterator it )
    {
        _ptr = it;
        _value = std::make_unique<MatrixValue>(*_ptr);
    }


    // Pre-incrementable: ++it.
    iterator& operator++()
    {
        ++_ptr;
        *_value = *_ptr;

        return *this;
    }

    // Post-incrementable: it++.
    iterator operator++(int)
    {
        iterator i = *this;
        ++(*this);
        return i;
    }


    // Pre-decrementable: --it.
    iterator& operator--()
    {
        --_ptr;
        *_value = *_ptr;

        return *this;
    }

    // Post-decrementable: it--.
    iterator operator--(int)
    {
        iterator i = *this;
        --(*this);
        return i;
    }

    bool operator==(const iterator& rhs) const
    {
        return (_ptr == rhs._ptr);
    }

    bool operator!=( const iterator& rhs) const
    {
        return (_ptr != rhs._ptr) ;
    }

    typename iterator::reference operator*() const
    {
        return (*_value);
    }

    typename iterator::pointer operator->() const
    {
        return &(*_value);
    }

private:
    typename container::iterator _ptr;
    std::unique_ptr<MatrixValue> _value;
};