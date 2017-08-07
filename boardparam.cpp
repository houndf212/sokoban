#include "boardparam.h"
#include "roomslice.h"
#include <algorithm>

void BoardParam::set_matrix(const ElementsMatrix &m)
{
    m_room = m;

    for (auto row=m.zero(); row<m.row_size(); ++row) {
        for (auto col=m.zero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            auto e = m.get(p);
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
}

bool BoardParam::man_move(Direction &d)
{
    assert(d!=Direction::NotValid);

    Pos to = man_pos.move(d);

    if (!m_room.isInMatrix(to))
        return false;

    auto el = m_room.get(to);
    switch (el) {
    case Elements::wall:
        return false;
    case Elements::floor:
        man_pos = to;
        assert(!is_push(d));
        return true;
    case Elements::box: {
        Pos too = to.move(d);
        if (!m_room.isInMatrix(too))
            return false;

        if (m_room.get(too) == Elements::floor) {
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
    assert(box.to(to) != Direction::NotValid);
    assert(m_room.get(box) == Elements::box);
    assert(m_room.get(to) == Elements::floor);
    assert(box == Pos((man_pos.row()+to.row())/2, (man_pos.col()+to.col())/2));

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
            Pos man_to = box.move(reverse(d));
            Pos to = box.move(d);
            BoardParam pa = *this;
            //如果需要计算移动步骤，这里人是跳跃移动的
            pa.man_pos = man_to;
            pa.box_move(box, to);
            if (pa.is_goal(to) || !pa.is_absolutely_dead_box(to))
                nexts.push_back(pa);
        }
    };

    for (auto p : box_index) {
        func(p, Direction::up);
        func(p, Direction::down);
        func(p, Direction::left);
        func(p, Direction::right);
    }
    return nexts;
}

bool BoardParam::can_box_move(Pos box, Direction d) const
{
    assert(m_room.get(box) == Elements::box);
    Pos to = box.move(d);
    if (m_room.get(to) != Elements::floor) {
        return false;
    }

    Pos man_to = box.move(reverse(d));
    if (m_room.get(man_to) != Elements::floor) {
        return false;
    }

    RoomSlice s(*this);
    return s.can_man_to(man_to);
}

bool BoardParam::is_done() const
{
    for (auto p : m_goals) {
        if (m_room.get(p) != Elements::box)
            return false;
    }
    return true;
}

bool BoardParam::is_goal(Pos p) const
{
    return std::find(begin(m_goals), end(m_goals), p) != end(m_goals);
}

bool BoardParam::is_absolutely_dead_box(Pos box) const
{
    // 左上右下  相邻 两个方向都是 墙 那么一定死了
    assert(m_room.get(box) == Elements::box);
    //假定 board 周围必须有一堵墙卡住
    constexpr auto wall = Elements::wall;
    Pos left(box.row(), box.col()-1);
    Pos up(box.row()-1, box.col());
    Pos right(box.row(), box.col()+1);
    Pos down(box.row()+1, box.col());

    if ((m_room.get(left) == wall || m_room.get(right) == wall)
            && (m_room.get(up) == wall || m_room.get(down) == wall)) {
        return true;

    }
    return false;
}

bool BoardParam::is_absolutely_dead() const
{
    for (auto p : box_index) {
        if (!is_goal(p) && is_absolutely_dead_box(p))
            return true;
    }
    return false;
}

ElementsMatrix BoardParam::to_matrix() const
{
    ElementsMatrix m = m_room;

    m.set(man_pos, Elements::man);

    for (auto p : m_goals) {
        auto e = m.get(p);
        m.set(p, add_goal(e));
    }
    return m;
}

BoardParam BoardParam::to_goal() const
{
    BoardParam pa = *this;
    for (auto p : pa.box_index) {
        pa.m_room.set(p, Elements::floor);
    }

    pa.box_index.clear();
    for (auto p : pa.m_goals) {
        pa.m_room.set(p, Elements::box);
        pa.box_index.push_back(p);
    }
    return pa;
}

bool operator ==(const BoardParam &p1, const BoardParam &p2)
{
    assert(p1.goals() == p2.goals());

    // 这里需要特殊处理完成的状态，因为完成时人在哪里也不知道，所以特殊处理
    if (p1.is_done() && p2.is_done())
        return true;

    return p1.room() == p2.room() && RoomSlice(p1).can_man_to(p2.man());
}
