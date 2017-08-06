#include "boxmover.h"

#include <algorithm>
#include "board_api.h"
#include "roomslice.h"

// 左上右下  相邻 两个方向都是 墙 那么一定死了
bool BoxMover::is_absolutely_dead_box(Pos box, const BoardParam &param)
{
    assert(std::find(begin(param.box_index), end(param.box_index), box)!=end(param.box_index));
    //假定 board 周围必须有一堵墙卡住
    const auto &m = param.room;
    constexpr auto wall = Elements::wall;
    Pos left(box.row(), box.col()-1);
    Pos up(box.row()-1, box.col());
    Pos right(box.row(), box.col()+1);
    Pos down(box.row()+1, box.col());

    if ((m.get(left) == wall || m.get(right) == wall)
            && (m.get(up) == wall || m.get(down) == wall)) {
        return true;

    }
    return false;
}

bool BoxMover::is_absolutely_dead(const BoardParam &param)
{
    for (auto p : param.box_index) {
        if (!param.is_goal(p) && is_absolutely_dead_box(p, param))
            return true;
    }
    return false;
}

bool BoxMover::can_box_move(Pos box, Direction d, const BoardParam &param)
{
    Pos to = Board_API::move(box, d);
    if (param.room.get(to) != Elements::floor) {
        return false;
    }

    Pos man_to = Board_API::move(box, reverse(d));
    if (param.room.get(man_to) != Elements::floor) {
        return false;
    }

    RoomSlice s(param);
    return s.can_man_to(man_to);
}

std::list<BoardParam> BoxMover::next_move(const BoardParam &param)
{
    std::list<BoardParam> nexts;

    auto func = [&](Pos box, Direction d) {
        if (can_box_move(box, d, param)) {
            Pos man_to = Board_API::move(box, reverse(d));
            Pos to = Board_API::move(box, d);
            BoardParam pa = param;
            //如果需要计算移动步骤，这里人是跳跃移动的
            pa.man_pos = man_to;
            Board_API::box_move(pa, box, to);
            if (!BoxMover::is_absolutely_dead_box(to ,pa))
                nexts.push_back(pa);
        }
    };

    for (auto p : param.box_index) {
        func(p, Direction::up);
        func(p, Direction::down);
        func(p, Direction::left);
        func(p, Direction::right);
    }
    return nexts;
}
