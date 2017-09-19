#include "types.h"

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

bool check_matrix_iterator()
{
    check_range_iterator();
    check_row_iterator();
    check_col_iterator();
    return true;
}
