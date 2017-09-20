﻿#ifndef BASIC_RESIZE_MATRIX_H
#define BASIC_RESIZE_MATRIX_H
#include <vector>
#include <limits>
#include <assert.h>
#include "basic_pos.h"
#include "basic_matrix_iterator.h"
#include "basic_matrix_row_iterator.h"
#include "basic_matrix_col_iterator.h"
#include "iteratorrange.h"

template<typename T, typename S>
class Basic_Resize_Matrix
{
public:
    typedef T value_type;
    typedef S size_type;

    static constexpr size_type szero() { return S(0); }
    static constexpr value_type vmax() { return std::numeric_limits<value_type>::max(); }

    void resize(size_type row, size_type col)
    {
        n_row = row;
        n_col = col;

        std::vector<value_type> vec(n_col, value_type());
        mat = std::vector<std::vector<value_type>>(row, vec);
    }

    void resize(const std::pair<size_type, size_type> &p)
    {
        resize(p.first, p.second);
    }

    void fill(value_type val)
    {
        for (auto &vec : mat) {
            std::fill(std::begin(vec), std::end(vec), val);
        }
    }

    template<typename U>
    value_type get(Basic_Pos<U> p) const
    {
        assert(isInMatrix(p));
        return mat[p.row()][p.col()];
    }

    template<typename U>
    void set(Basic_Pos<U> p, value_type val)
    {
        assert(isInMatrix(p));
        mat[p.row()][p.col()] = val;
    }

    template<typename U>
    bool isInMatrix(Basic_Pos<U> p) const
    {
        return 0<=p.row() && p.row()<row_size() && 0<=p.col() && p.col()<col_size();
    }

    size_type row_size() const { return n_row; }
    size_type col_size() const { return n_col; }

    std::pair<size_type, size_type> size() const
    {
        return std::make_pair(row_size(), col_size());
    }

    bool equal(const Basic_Resize_Matrix& bm) const
    {
        assert(size()==bm.size());
        return mat == bm.mat;
    }

    bool less(const Basic_Resize_Matrix& bm) const
    {
        assert(size()==bm.size());
        return mat < bm.mat;
    }

private:
    size_type n_row;
    size_type n_col;
    std::vector<std::vector<value_type>> mat;

private:
    value_type &iter_ref(const Basic_Pos<size_type> &p)
    {
        assert(isInMatrix(p));
        return mat[p.row()][p.col()];
    }

    const value_type &iter_ref(const Basic_Pos<size_type> &p) const
    {
        assert(isInMatrix(p));
        return mat[p.row()][p.col()];
    }
    //迭代器
    friend class Basic_Matrix_Iterator<Basic_Resize_Matrix>;
    typedef Basic_Matrix_Iterator<Basic_Resize_Matrix> iterator;

    friend class Basic_Matrix_Iterator<const Basic_Resize_Matrix, const value_type>;
    typedef Basic_Matrix_Iterator<const Basic_Resize_Matrix, const value_type> const_iterator;

    typedef std::reverse_iterator<iterator>            reverse_iterator;
    typedef std::reverse_iterator<const_iterator>      const_reverse_iterator;

    //行迭代器
    friend class Basic_Matrix_Row_Iterator<Basic_Resize_Matrix>;
    typedef Basic_Matrix_Row_Iterator<Basic_Resize_Matrix> row_iterator;

    friend class Basic_Matrix_Row_Iterator<const Basic_Resize_Matrix, const value_type>;
    typedef Basic_Matrix_Row_Iterator<const Basic_Resize_Matrix, const value_type> const_row_iterator;

    typedef std::reverse_iterator<row_iterator>            row_reverse_iterator;
    typedef std::reverse_iterator<const_row_iterator>      const_row_reverse_iterator;

    //列迭代器
    friend class Basic_Matrix_Col_Iterator<Basic_Resize_Matrix>;
    typedef Basic_Matrix_Col_Iterator<Basic_Resize_Matrix> col_iterator;

    friend class Basic_Matrix_Col_Iterator<const Basic_Resize_Matrix, const value_type>;
    typedef Basic_Matrix_Col_Iterator<const Basic_Resize_Matrix, const value_type> const_col_iterator;

    typedef std::reverse_iterator<col_iterator>            col_reverse_iterator;
    typedef std::reverse_iterator<const_col_iterator>      const_col_reverse_iterator;

public:
    IteratorRange<iterator> range()
    {
        return {begin(), end()};
    }

    IteratorRange<const_iterator> range() const
    {
        return {begin(), end()};
    }

    IteratorRange<reverse_iterator> reverse_range()
    {
        return {rbegin(), rend()};
    }

    IteratorRange<const_reverse_iterator> reverse_range() const
    {
        return {rbegin(), rend()};
    }

    iterator begin() { return iterator(this, 0, 0); }
    iterator end() { return iterator(this, row_size(), 0); }

    const_iterator begin() const { return const_iterator(this, 0, 0); }
    const_iterator end() const { return const_iterator(this, row_size(), 0); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    // row range
    IteratorRange<row_iterator> row_range(size_type row)
    {
        assert(row<row_size());
        return {row_iterator(this, row, 0),
                    row_iterator(this, row, col_size())};
    }

    IteratorRange<const_row_iterator> row_range(size_type row) const
    {
        assert(row<row_size());
        return {const_row_iterator(this, row, 0),
                    const_row_iterator(this, row, col_size())};
    }


    IteratorRange<row_reverse_iterator> row_reverse_range(size_type row)
    {
        assert(row<row_size());
        return {row_reverse_iterator(row_iterator(this, row, col_size())),
                    row_reverse_iterator(row_iterator(this, row, 0))};
    }

    IteratorRange<const_row_reverse_iterator> row_reverse_range(size_type row) const
    {
        assert(row<row_size());
        return {const_row_reverse_iterator(const_row_iterator(this, row, col_size())),
                    const_row_reverse_iterator(const_row_iterator(this, row, 0))};
    }

    //col range
    IteratorRange<col_iterator> col_range(size_type col)
    {
        assert(col<col_size());
        return {col_iterator(this, 0, col),
                    col_iterator(this, row_size(), col)};
    }

    IteratorRange<const_col_iterator> col_range(size_type col) const
    {
        assert(col<col_size());
        return {const_col_iterator(this, 0, col),
                    const_col_iterator(this, row_size(), col)};
    }

    IteratorRange<col_reverse_iterator> col_reverse_range(size_type col)
    {
        assert(col<col_size());
        return {col_reverse_iterator(col_iterator(this,row_size(), col)),
                    col_reverse_iterator(col_iterator(this, 0, col))};
    }

    IteratorRange<const_col_reverse_iterator> col_reverse_range(size_type col) const
    {
        assert(col<col_size());
        return {const_col_reverse_iterator(const_col_iterator(this, row_size(), col)),
                    const_col_reverse_iterator(const_col_iterator(this, 0, col))};
    }
};

template<typename T, typename S>
inline bool operator == (const Basic_Resize_Matrix<T, S> &a, const Basic_Resize_Matrix<T, S> &b)
{
    return a.equal(b);
}

#endif // BASIC_RESIZE_MATRIX_H
