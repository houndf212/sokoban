#include "types.h"
#include "debug_print.h"

void test_print()
{
    Pos p(1, 2);
    print(p);

    ElementsMatrix m;
    m.resize(3, 3);
    m.fill(Elements::Space);

    m.set(Pos(0,0), Elements::Man);

    m.set(Pos(0,1), Elements::Box);

    m.set(Pos(0,2), Elements::Destination);

    print(m);
}
