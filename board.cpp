#include "board.h"
#include "board_api.h"

void Board::setMatrix(const ElementsMatrix &m)
{
    matrix = m;
    des_vec.clear();
    for (auto row=m.zero(); row<m.row_size(); ++row) {
        for (auto col=m.zero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            auto e = m.get(p);
            switch (e) {
            case Elements::man:
                man_pos = p;
                matrix.set(p, Elements::floor);
                break;
//            case Elements::Box:
//                box_vec.push_back(p);
//                break;
            case Elements::goal:
                des_vec.push_back(p);
                matrix.set(p, Elements::floor);
                break;
            default:
                break;
            }
        }
    }
}

bool Board::move(Direction &d)
{
    assert(d!=Direction::NotValid);

    Pos to = man_pos;
    Board_API::move(&to, d);

    if (!matrix.isInMatrix(to))
        return false;

    auto el = matrix.get(to);
    switch (el) {
    case Elements::wall:
        return false;
    case Elements::floor:
        man_pos = to;
        assert(!is_push(d));
        return true;
    case Elements::box:
    {
        Pos too = to;
        Board_API::move(&too, d);
        if (!matrix.isInMatrix(too))
            return false;

        if (matrix.get(too) == Elements::floor) {
            matrix.set(to, Elements::floor);
            matrix.set(too, Elements::box);
            man_pos = to;
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

bool Board::is_done() const
{
    for (auto p : des_vec) {
        if (matrix.get(p) != Elements::box)
            return false;
    }
    return true;
}

ElementsMatrix Board::to_matrix() const
{
    ElementsMatrix m = matrix;

    m.set(man_pos, Elements::man);
    for (auto p : des_vec) {
        auto e = m.get(p);
        m.set(p, add_goal(e));
    }
    return m;
}
