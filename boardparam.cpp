#include "boardparam.h"
#include <algorithm>

BoardParam &BoardParam::operator=(const BoardParam &param)
{
    man_pos = param.man_pos;
    const_cast<PosVector&>(goals) = param.goals;
    room = param.room;
    box_index = param.box_index;
    return *this;
}

void BoardParam::set_matrix(const ElementsMatrix &m)
{
    room = m;
    PosVector vec;

    for (auto row=m.zero(); row<m.row_size(); ++row) {
        for (auto col=m.zero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            auto e = m.get(p);
            switch (e) {
            case Elements::man:
                man_pos = p;
                room.set(p, Elements::floor);
                break;
            case Elements::box:
                box_index.push_back(p);
                break;
            case Elements::goal:
                vec.push_back(p);
                room.set(p, Elements::floor);
                break;
            default:
                break;
            }
        }
    }
    const_cast<PosVector&>(goals) = vec;
}

bool BoardParam::is_goal(Pos p) const
{
    return std::find(begin(goals), end(goals), p) != end(goals);
}

BoardParam BoardParam::to_goal() const
{
    BoardParam pa = *this;
    for (auto p : pa.box_index) {
        pa.room.set(p, Elements::floor);
    }

    pa.box_index.clear();
    for (auto p : pa.goals) {
        pa.room.set(p, Elements::box);
        pa.box_index.push_back(p);
    }
    return pa;
}
