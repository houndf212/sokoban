#ifndef BASIC_RESIZE_MATRIX_H
#define BASIC_RESIZE_MATRIX_H
#include <vector>
#include <assert.h>
#include "basic_pos.h"

template<typename T, typename S>
class Basic_Resize_Matrix
{
public:
    typedef T value_type;
    typedef S size_type;

    void resize(size_type row, size_type col)
    {
        n_row = row;
        n_col = col;

        std::vector<value_type> vec(n_col, value_type());
        m = std::vector<std::vector<value_type>>(row, vec);
    }

    void fill(value_type val)
    {
        for (auto &vec : m) {
            std::fill(begin(vec), end(vec), val);
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

    bool equal(const Basic_Resize_Matrix& bm)
    {
        assert(row_size() == bm.row_size());
        assert(col_size() == bm.col_size());
        return m == bm.m;
    }

    bool less(const Basic_Resize_Matrix& bm)
    {
        assert(row_size() == bm.row_size());
        assert(col_size() == bm.col_size());
        return m < bm.m;
    }

private:
    size_type n_row;
    size_type n_col;
    std::vector<std::vector<value_type>> m;
};

//template<typename T, typename S>
//bool operator == (const Basic_Resize_Matrix<T, S> &a, const Basic_Resize_Matrix<T, S> &a)
//{
//    return a.equal(b);
//}

#endif // BASIC_RESIZE_MATRIX_H
