#include "types.h"
#include <numeric>
#include <algorithm>

void check_range_iterator()
{
    IntMatrix m;
    m.resize(2, 2);

    int i=1;
    for (auto &v : m.range()) {
        v = i++;
    }

    i = 1;
    assert(m.get(Pos(0, 0)) == i++);
    assert(m.get(Pos(0, 1)) == i++);
    assert(m.get(Pos(1, 0)) == i++);
    assert(m.get(Pos(1, 1)) == i++);

    const IntMatrix &cm = m;
    i = 1;
    for (auto &v : cm.range()) {
        assert(v == i++);
    }
}

void check_row_iterator()
{
    IntMatrix m;
    m.resize(2, 2);
    int i=10;
    for (auto &v : m.row_range(0)) {
        v = i;
        i+=10;
    }
    assert(m.get(Pos(0, 0)) == 10);
    assert(m.get(Pos(0, 1)) == 20);

    i=100;
    for (auto &v : m.row_range(1)) {
        v = i;
        i+=100;
    }
    assert(m.get(Pos(1, 0)) == 100);
    assert(m.get(Pos(1, 1)) == 200);
}

void check_col_iterator()
{
    IntMatrix m;
    m.resize(2, 2);
    int i=10;
    for (auto &v : m.col_range(0)) {
        v = i;
        i+=10;
    }
    assert(m.get(Pos(0, 0)) == 10);
    assert(m.get(Pos(1, 0)) == 20);

    i=100;
    for (auto &v : m.col_range(1)) {
        v = i;
        i+=100;
    }
    assert(m.get(Pos(0, 1)) == 100);
    assert(m.get(Pos(1, 1)) == 200);
}

void check_range_min_max()
{
    int n = 100;
    while(n-->0) {
        IntMatrix m;
        m.resize(2, 3);

        std::vector<IntMatrix::value_type> vec(m.row_size()*m.col_size(), 0);
        std::iota(begin(vec), end(vec), n);
        std::random_shuffle(begin(vec), end(vec));

        std::copy(begin(vec), end(vec), m.begin());
        auto iter_min = std::min_element(m.begin(), m.end());
        assert(*iter_min == n);
        auto iter_max = std::max_element(m.begin(), m.end());
        assert(*iter_max == n+int(vec.size())-1);
    }
}

void check_row_min_max()
{
    int n = 100;
    while(n-->0) {
        IntMatrix m;
        m.resize(4, 4);

        std::vector<IntMatrix::value_type> vec(m.col_size(), 0);
        std::iota(begin(vec), end(vec), n);
        std::random_shuffle(begin(vec), end(vec));

        auto range = m.row_range(2);
        std::copy(begin(vec), end(vec), range.begin());
        auto iter_min = std::min_element(range.begin(),range.end());
        assert(*iter_min == n);
        auto iter_max = std::max_element(range.begin(),range.end());
        assert(*iter_max == n+int(vec.size())-1);
    }
}

void check_col_min_max()
{
    int n = 100;
    while(n-->0) {
        IntMatrix m;
        m.resize(5, 6);

        std::vector<IntMatrix::value_type> vec(m.row_size(), 0);
        std::iota(begin(vec), end(vec), n);
        std::random_shuffle(begin(vec), end(vec));

        auto range = m.col_range(3);
        std::copy(begin(vec), end(vec), range.begin());
        auto iter_min = std::min_element(range.begin(),range.end());
        assert(*iter_min == n);
        auto iter_max = std::max_element(range.begin(),range.end());
        assert(*iter_max == n+int(vec.size())-1);
    }
}

bool check_matrix_iterator()
{
    check_range_iterator();
    check_row_iterator();
    check_col_iterator();

    check_range_min_max();
    check_row_min_max();
    check_col_min_max();
    return true;
}
