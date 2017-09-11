#include "roomslice.h"

RoomSlice::RoomSlice(const BoardParam &pa)
    :param(pa)
{
    const auto &matrix = param.room();

    slice.resize(matrix.size());
    slice.fill(k_unflagged);

    IntMatrix::value_type g = 1;
    auto range = matrix.range();
    for (auto it=range.first; it!=range.second; ++it) {
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

