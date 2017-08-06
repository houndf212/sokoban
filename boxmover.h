#ifndef BOXMOVER_H
#define BOXMOVER_H
#include "boardparam.h"

namespace BoxMover
{
bool is_absolutely_dead_box(Pos box, const BoardParam &param);
bool is_absolutely_dead(const BoardParam &param);

bool can_box_move(Pos box, Direction d, const BoardParam &param);

std::list<BoardParam> next_move(const BoardParam &param);
}

#endif // BOXMOVER_H
