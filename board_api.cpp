#include "board_api.h"

void Board_API::swap_pos(ElementsMatrix *m, Pos p1, Pos p2)
{
    auto e = m->get(p1);
    m->set(p1, m->get(p2));
    m->set(p2, e);
}

void Board_API::move(Pos *p, Direction d)
{
    switch (d) {
    case Direction::up:
        p->row()--;
        break;
    case Direction::down:
        p->row()++;
        break;
    case Direction::left:
        p->col()--;
        break;
    case Direction::right:
        p->col()++;
        break;
    default:
        assert(false);
        break;
    }
}
