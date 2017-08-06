﻿#ifndef BOARD_API_H
#define BOARD_API_H
#include "boardparam.h"

namespace Board_API
{
    void swap_pos(ElementsMatrix &m, Pos p1, Pos p2);
    Pos move(Pos p, Direction d);

    bool man_move(BoardParam &param, Direction &d);
    void box_move(BoardParam &param, Pos box, Pos to);

    bool is_done(const BoardParam &param);
    ElementsMatrix to_matrix(const BoardParam &param);
}

#endif // BOARD_API_H
