#include "types.h"

void test_print()
{
    Pos p(1, 2);
    print(p);

    ElementsMatrix m;
    m.resize(3, 3);
    m.fill(Elements::floor);

    m.set(Pos(0,0), Elements::man);

    m.set(Pos(0,1), Elements::box);

    m.set(Pos(0,2), Elements::goal);

    print(m);
}
