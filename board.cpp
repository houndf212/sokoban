#include "board.h"
#include "board_api.h"

Board::Board(const ElementsMatrix &m)
{
    matrix = m;
    for (auto x=0; x<m.row_size(); ++x) {
        for (auto y=0; y<m.col_size(); ++y) {
            Pos p(x, y);
            auto e = m.get(p);
            switch (e) {
            case Elements::Man:
                man_pos = p;
                matrix.set(p, Elements::Space);
                break;
//            case Elements::Box:
//                box_vec.push_back(p);
//                break;
            case Elements::Destination:
                des_vec.push_back(p);
                matrix.set(p, Elements::Space);
                break;
            default:
                break;
            }
        }
    }
}

bool Board::move(Direction d)
{
    assert(d!=Direction::NotValid);
    assert(!is_push(d));

    Pos to = man_pos;
    Board_API::move(&to, d);

    if (!matrix.isInMatrix(to))
        return false;

    auto el = matrix.get(to);
    switch (el) {
    case Elements::Wall:
        return false;
    case Elements::Space:
        man_pos = to;
        return true;
    case Elements::Box:
    {
        Pos too = to;
        Board_API::move(&too, d);
        if (!matrix.isInMatrix(too))
            return false;

        if (matrix.get(too) == Elements::Space) {
            matrix.set(to, Elements::Space);
            matrix.set(too, Elements::Box);
            man_pos = to;
            return true;
        }

        assert(matrix.get(too) == Elements::Wall);
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
        if (matrix.get(p) != Elements::Box)
            return false;
    }
    return true;
}

ElementsMatrix Board::to_matrix() const
{
    ElementsMatrix m = matrix;

    for (auto p : des_vec) {
        if (m.get(p) != Elements::Box)
            m.set(p, Elements::Destination);
    }
    m.set(man_pos, Elements::Man);

    return m;
}
