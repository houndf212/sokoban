#include "boardparam.h"
#include "roomslice.h"
#include <algorithm>

void BoardParam::set_matrix(const ElementsMatrix &m)
{
    m_room = m;
    m_goals.clear();
    box_index.clear();

    for (auto it=m.range(); it; ++it) {
        Pos p = it.pos();
        auto e = *it;
        switch (e) {
        case Elements::man:
            man_pos = p;
            m_room.set(p, Elements::floor);
            break;
        case Elements::box:
            box_index.push_back(p);
            break;
        case Elements::goal:
            m_goals.push_back(p);
            m_room.set(p, Elements::floor);
            break;
        case Elements::man_goal:
            man_pos = p;
            m_goals.push_back(p);
            m_room.set(p, Elements::floor);
            break;
        case Elements::box_goal:
            box_index.push_back(p);
            m_goals.push_back(p);
            m_room.set(p, Elements::box);
            break;
        default:
            break;
        }
    }
}

bool BoardParam::man_move(Direction &d)
{
    assert(d!=Direction::NotValid);

    Pos to = pos_move(man(), d);

    if (!room().isInMatrix(to))
        return false;

    auto el = room().get(to);
    switch (el) {
    case Elements::wall:
        return false;
    case Elements::floor:
        man_pos = to;
        assert(!is_push(d));
        return true;
    case Elements::box: {
        Pos too = pos_move(to, d);
        if (!room().isInMatrix(too))
            return false;

        if (room().get(too) == Elements::floor) {
            box_move(to, too);
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

void BoardParam::box_move(Pos box, Pos to)
{
    assert(pos_to(box, to) != Direction::NotValid);
    assert(room().isInMatrix(box));
    assert(room().isInMatrix(to));
    assert(room().get(box) == Elements::box);
    assert(room().get(to) == Elements::floor);
    assert(box == Pos((man().row()+to.row())/2, (man().col()+to.col())/2));

    man_pos = box;
    m_room.set(box, Elements::floor);
    m_room.set(to, Elements::box);

    auto it = std::find(begin(box_index), end(box_index), box);
    assert(it != end(box_index));
    *it = to;
}

std::list<BoardParam> BoardParam::next_move() const
{
    std::list<BoardParam> nexts;

    auto func = [&](Pos box, Direction d) {
        if (can_box_move(box, d)) {
            Pos man_to = pos_move(box, reverse(d));
            Pos to = pos_move(box, d);
            BoardParam pa = *this;
            //如果需要计算移动步骤，这里人是跳跃移动的
            pa.man_pos = man_to;
            pa.box_move(box, to);
            if (pa.is_goal(to) || !pa.is_absolutely_dead_box(to))
                nexts.push_back(pa);
        }
    };

    for (auto p : boxes()) {
        func(p, Direction::up);
        func(p, Direction::down);
        func(p, Direction::left);
        func(p, Direction::right);
    }
    return nexts;
}

bool BoardParam::can_box_move(Pos box, Direction d) const
{
    assert(room().isInMatrix(box));
    assert(room().get(box) == Elements::box);
    Pos to = pos_move(box, d);
    if (room().get(to) != Elements::floor) {
        return false;
    }

    Pos man_to = pos_move(box, reverse(d));
    if (room().get(man_to) != Elements::floor) {
        return false;
    }

    RoomSlice s(*this);
    return s.can_man_to(man_to);
}

bool BoardParam::precise_equal(const BoardParam &param) const
{
    assert(goals() == param.goals());
    return man() == param.man()
            && room() == param.room();
}

bool BoardParam::like_equal(const BoardParam &param) const
{
    assert(goals() == param.goals());
    return room() == param.room() && RoomSlice(*this).can_man_to(param.man());
}

bool BoardParam::is_done() const
{
    auto is_box = [this](const Pos &p) { return room().get(p) == Elements::box; };
    return std::all_of(begin(goals()), end(goals()), is_box);
}

bool BoardParam::is_goal(Pos p) const
{
    return std::find(begin(goals()), end(goals()), p) != end(goals());
}

bool BoardParam::is_absolutely_dead_box(Pos box) const
{
    // 左上右下  相邻 两个方向都是 墙 那么一定死了
    assert(room().get(box) == Elements::box);
    //假定 board 周围必须有一堵墙卡住
    constexpr auto wall = Elements::wall;
    Pos left(box.row(), box.col()-1);
    Pos up(box.row()-1, box.col());
    Pos right(box.row(), box.col()+1);
    Pos down(box.row()+1, box.col());

    if ((room().get(left) == wall || room().get(right) == wall)
            && (room().get(up) == wall || room().get(down) == wall)) {
        return true;

    }
    return false;
}

bool BoardParam::is_absolutely_dead() const
{
    auto dead_box = [this](const Pos &p) { return !is_goal(p) && is_absolutely_dead_box(p); };
    return std::any_of(begin(boxes()), end(boxes()), dead_box);
}

ElementsMatrix BoardParam::to_matrix() const
{
    ElementsMatrix m = room();

    m.set(man(), Elements::man);

    for (auto p : goals()) {
        auto e = m.get(p);
        m.set(p, add_goal(e));
    }
    return m;
}

BoardParam BoardParam::to_goal() const
{
    BoardParam pa = *this;
    for (auto p : pa.boxes()) {
        pa.m_room.set(p, Elements::floor);
    }

    pa.box_index = pa.goals();
    for (auto p : pa.boxes()) {
        pa.m_room.set(p, Elements::box);
    }
    return pa;
}

bool BoardParam::can_solve(const MoveList &mlst) const
{
    BoardParam param = *this;

    for (auto d : mlst) {
        if (!param.man_move(d))
            return false;
    }
    return param.is_done();
}

bool operator ==(const BoardParam &p1, const BoardParam &p2)
{
    assert(p1.goals() == p2.goals());

    // 这里需要特殊处理完成的状态，因为完成时人在哪里也不知道，所以特殊处理
    if (p1.is_done() && p2.is_done())
        return true;

    return p1.room() == p2.room() && RoomSlice(p1).can_man_to(p2.man());
}
