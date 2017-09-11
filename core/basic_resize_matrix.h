#ifndef BASIC_RESIZE_MATRIX_H
#define BASIC_RESIZE_MATRIX_H
#include <vector>
#include <limits>
#include <assert.h>
#include "basic_pos.h"

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
        m = std::vector<std::vector<value_type>>(row, vec);
    }

    void resize(const std::pair<size_type, size_type> &p)
    {
        resize(p.first, p.second);
    }

    void fill(value_type val)
    {
        for (auto &vec : m) {
            std::fill(std::begin(vec), std::end(vec), val);
        }
    }

    template<typename U>
    value_type get(Basic_Pos<U> p) const
    {
        assert(isInMatrix(p));
        return m[p.row()][p.col()];
    }

    template<typename U>
    void set(Basic_Pos<U> p, value_type val)
    {
        assert(isInMatrix(p));
        m[p.row()][p.col()] = val;
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
        return m == bm.m;
    }

    bool less(const Basic_Resize_Matrix& bm) const
    {
        assert(size()==bm.size());
        return m < bm.m;
    }

private:
    size_type n_row;
    size_type n_col;
    std::vector<std::vector<value_type>> m;

private:
    //简单实现一个迭代器
    class iterator
    {
        typedef value_type& reference;
        friend class Basic_Resize_Matrix;
        iterator(Basic_Resize_Matrix *m, size_type row, size_type col)
            :matrix(m), p(row, col)
        {}
    public:
        Basic_Pos<size_type> pos() const
        {
            return p;
        }

        reference operator*() const
        {
            return matrix->m[p.row()][p.col()];
        }

        iterator& operator++()
        {
            p.col()++;
            p.row() += p.col() / matrix->col_size();
            p.col() %= matrix->col_size();
            return *this;
        }

        bool operator !=(const iterator &right) const
        {
            assert(matrix == right.matrix);
            return  p != right.p;
        }
    private:
        Basic_Resize_Matrix *matrix;
        Basic_Pos<size_type> p;
    };

    class const_iterator
    {
        typedef const value_type& reference;
        friend class Basic_Resize_Matrix;
        const_iterator(const Basic_Resize_Matrix *m, size_type row, size_type col)
            :matrix(m), p(row, col)
        {}
    public:
        Basic_Pos<size_type> pos() const
        {
            return p;
        }

        reference operator*() const
        {
            return matrix->m[p.row()][p.col()];
        }

        const_iterator& operator++()
        {
            p.col()++;
            p.row() += p.col() / matrix->col_size();
            p.col() %= matrix->col_size();
            return *this;
        }

        bool operator !=(const const_iterator &right) const
        {
            assert(matrix == right.matrix);
            return  p != right.p;
        }
    private:
        const Basic_Resize_Matrix *matrix;
        Basic_Pos<size_type> p;
    };
public:
    std::pair<iterator, iterator> range()
    {
        return std::make_pair(iterator(this, 0, 0),
                              iterator(this, row_size(), 0));
    }

    std::pair<const_iterator, const_iterator> range() const
    {
        return std::make_pair(const_iterator(this, 0, 0),
                              const_iterator(this, row_size(), 0));
    }

    iterator begin() { return iterator(this, 0, 0); }
    iterator end() { return iterator(this, row_size(), 0); }

    const_iterator begin() const { return const_iterator(this, 0, 0); }
    const_iterator end() const { return const_iterator(this, row_size(), 0); }
};

template<typename T, typename S>
inline bool operator == (const Basic_Resize_Matrix<T, S> &a, const Basic_Resize_Matrix<T, S> &b)
{
    return a.equal(b);
}

#endif // BASIC_RESIZE_MATRIX_H
