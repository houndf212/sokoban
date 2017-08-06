#include "board_api.h"
#include <algorithm>

void Board_API::swap_pos(ElementsMatrix &m, Pos p1, Pos p2)
{
    auto e = m.get(p1);
    m.set(p1, m.get(p2));
    m.set(p2, e);
}

Pos Board_API::move(Pos p, Direction d)
{
    Pos to = p;
    switch (d) {
    case Direction::up:
        to.row()--;
        break;
    case Direction::down:
        to.row()++;
        break;
    case Direction::left:
        to.col()--;
        break;
    case Direction::right:
        to.col()++;
        break;
    default:
        assert(false);
        break;
    }
    return to;
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

    Pos to = Board_API::move(param.man_pos, d);

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
    case Elements::box: {
        Pos too = Board_API::move(to, d);
        if (!param.room.isInMatrix(too))
            return false;

        if (param.room.get(too) == Elements::floor) {
            Board_API::box_move(param, to, too);
            d = add_push(d);
            return true;
        }
        return false;
    }
    default:
        break;
    }
    assert(false);
    return false;
}

void Board_API::box_move(BoardParam &param, Pos box, Pos to)
{
    assert(param.room.get(box) == Elements::box);
    assert(param.room.get(to) == Elements::floor);
    assert(box == Pos((param.man_pos.row()+to.row())/2, (param.man_pos.col()+to.col())/2));

    param.man_pos = box;
    param.room.set(box, Elements::floor);
    param.room.set(to, Elements::box);

    auto it = std::find(begin(param.box_index), end(param.box_index), box);
    assert(it != end(param.box_index));
    *it = to;
}
