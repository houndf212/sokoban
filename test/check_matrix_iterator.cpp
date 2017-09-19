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



void check_matrix_iterator()
{
    check_range_iterator();
}
