#include "roomslice.h"

RoomSlice::RoomSlice(const BoardParam &pa)
    :param(pa)
    ,slice(param.room().row_size(), param.room().col_size(), k_unflagged)
{
    const auto &matrix = param.room();

    IntMatrix::value_type g = 1;
    for (auto it=matrix.range(); it; ++it) {
        Pos p = it.pos();
        if (slice.get(p) != k_unflagged)
            continue;

        auto e = *it;
        if (e!=Elements::floor) {
            slice.set(p, k_block);
            continue;
        }

        seedPos(p, g);
        ++g;
    }
}

bool RoomSlice::can_man_to(Pos p) const
{
    assert(slice.isInMatrix(p));
    return slice.get(p) == slice.get(param.man());
}

void RoomSlice::seedPos(Pos p, IntMatrix::value_type val)
{
    if (slice.isInMatrix(p)
            && slice.get(p)==k_unflagged
            && param.room().get(p) == Elements::floor) {

        slice.set(p, val);
        seedPos(Pos(p.row()+1, p.col()), val);
        seedPos(Pos(p.row()-1, p.col()), val);
        seedPos(Pos(p.row(), p.col()+1), val);
        seedPos(Pos(p.row(), p.col()-1), val);
    }
}

