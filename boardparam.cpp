#include "boardparam.h"

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
