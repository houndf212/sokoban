#ifndef BOARDPARAM_H
#define BOARDPARAM_H
#include "types.h"
#include "movelist.h"

//这个类描述一个推箱子所有需要的元素，在boardapi操作这个类

class BoardParam
{
public:
    void set_matrix(const ElementsMatrix &m);

    bool man_move(Direction &d);

    const Pos &man() const { return man_pos; }

    type_size goals_size() const { return m_goals.size(); }
    const PosVector &goals() const { return m_goals; }
    const PosVector &boxes() const { return box_index; }

    const ElementsMatrix &room() const { return m_room; }

    std::list<BoardParam> next_move() const;

    bool is_done() const;

    bool is_goal(Pos p) const;

    bool is_absolutely_dead_box(Pos box) const;

    bool is_absolutely_dead() const;

    ElementsMatrix to_matrix() const;

    BoardParam to_goal() const;

    bool can_solve(const MoveList &mlst) const;
private:
    void box_move(Pos box, Pos to);
    bool can_box_move(Pos box, Direction d) const;
public:
    bool precise_equal(const BoardParam &param) const;
    bool like_equal(const BoardParam &param) const;
private:
    //人所在的位置
    Pos man_pos;
    //目标位置
    PosVector m_goals;
    //只包含 wall floor box
    ElementsMatrix m_room;
    // box 的索引
    PosVector box_index;
};

bool operator == (const BoardParam &p1, const BoardParam &p2);

#endif // BOARDPARAM_H
