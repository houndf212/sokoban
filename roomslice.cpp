#include "roomslice.h"
#include "debug_print.h"

RoomSlice::RoomSlice(const BoardParam &pa)
    :param(pa)
{
    const auto &matrix = param.room();

    slice.resize(matrix.row_size(), matrix.col_size());
    slice.fill(k_unflagged);

    IntMatrix::value_type g = 1;
    for (auto row=matrix.zero(); row<matrix.row_size(); ++row) {
        for (auto col=matrix.zero(); col<matrix.col_size(); ++col) {
            Pos p(row, col);

            if (slice.get(p) != k_unflagged)
                continue;

            auto e = matrix.get(p);
            if (e!=Elements::floor) {
                slice.set(p, k_block);
                continue;
            }

            seedPos(p, g);
            ++g;
        }
    }
}

bool RoomSlice::can_man_to(Pos p) const
{
    return slice.get(p) == slice.get(param.man());
}

void RoomSlice::seedPos(Pos p, int val)
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

