#include "board_api.h"

void Board_API::swap_pos(ElementsMatrix &m, Pos p1, Pos p2)
{
    auto e = m.get(p1);
    m.set(p1, m.get(p2));
    m.set(p2, e);
}

void Board_API::move(Pos &p, Direction d)
{
    switch (d) {
    case Direction::up:
        p.row()--;
        break;
    case Direction::down:
        p.row()++;
        break;
    case Direction::left:
        p.col()--;
        break;
    case Direction::right:
        p.col()++;
        break;
    default:
        assert(false);
        break;
    }
}

bool Board_API::is_done(const BoardParam &param)
{
    for (auto p : param.goals) {
        if (param.room.get(p) != Elements::box)
            return false;
    }
    return true;
}

ElementsMatrix Board_API::to_matrix(const BoardParam &param)
{
    ElementsMatrix m = param.room;

    m.set(param.man_pos, Elements::man);

    for (auto p : param.goals) {
        auto e = m.get(p);
        m.set(p, add_goal(e));
    }
    return m;
}

bool Board_API::man_move(BoardParam &param, Direction &d)
{
    assert(d!=Direction::NotValid);

    Pos to = param.man_pos;
    Board_API::move(to, d);

    if (!param.room.isInMatrix(to))
        return false;

    auto el = param.room.get(to);
    switch (el) {
    case Elements::wall:
        return false;
    case Elements::floor:
        param.man_pos = to;
        assert(!is_push(d));
        return true;
    case Elements::box:
    {
        Pos too = to;
        Board_API::move(too, d);
        if (!param.room.isInMatrix(too))
            return false;

        if (param.room.get(too) == Elements::floor) {
            param.room.set(to, Elements::floor);
            param.room.set(too, Elements::box);
            param.man_pos = to;
            d = add_push(d);
            return true;
        }
        return false;
    }
        break;
    default:
        assert(false);
        break;
    }
    return false;
}
