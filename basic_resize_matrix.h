#ifndef BASIC_RESIZE_MATRIX_H
#define BASIC_RESIZE_MATRIX_H
#include <vector>
#include <assert.h>
#include "basic_pos.h"

template<typename T, typename S = int>
class Basic_Resize_Matrix
{
public:
    typedef T value_type;
    typedef S size_type;

    void resize(size_type x, size_type y)
    {
        n_x = x;
        n_y = y;

        std::vector<value_type> vec(n_y, value_type());
        m = std::vector<std::vector<value_type>>(x, vec);
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
        return m[p.x()][p.y()];
    }

    template<typename U>
    void set(Basic_Pos<U> p, value_type val)
    {
        assert(isInMatrix(p));
        m[p.x()][p.y()] = val;
    }

    template<typename U>
    bool isInMatrix(Basic_Pos<U> p) const
    {
        return 0<=p.x() && p.x()<x_size() && 0<=p.y() && p.y()<y_size();
    }

    size_type x_size() const { return n_x; }
    size_type y_size() const { return n_y; }

    bool equal(const Basic_Resize_Matrix& bm)
    {
        assert(x_size() == bm.x_size());
        assert(y_size() == bm.y_size());
        return m == bm.m;
    }

    bool less(const Basic_Resize_Matrix& bm)
    {
        assert(x_size() == bm.x_size());
        assert(y_size() == bm.y_size());
        return m < bm.m;
    }

private:
    size_type n_x;
    size_type n_y;
    std::vector<std::vector<value_type>> m;
};

//template<typename T, typename S>
//bool operator == (const Basic_Resize_Matrix<T, S> &a, const Basic_Resize_Matrix<T, S> &a)
//{
//    return a.equal(b);
//}

#endif // BASIC_RESIZE_MATRIX_H
