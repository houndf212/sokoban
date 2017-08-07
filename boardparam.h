#ifndef BOARDPARAM_H
#define BOARDPARAM_H
#include "types.h"

//这个类描述一个推箱子所有需要的元素，在boardapi操作这个类

class BoardParam
{
public:
    BoardParam &operator=(const BoardParam &param);

    void set_matrix(const ElementsMatrix &m);

    bool man_move(Direction &d);

    std::list<BoardParam> next_move() const;
private:
    void box_move(Pos box, Pos to);
    bool can_box_move(Pos box, Direction d) const;
public:
    bool is_done() const;

    bool is_goal(Pos p) const;

    bool is_absolutely_dead_box(Pos box) const;

    bool is_absolutely_dead() const;

    ElementsMatrix to_matrix() const;

    BoardParam to_goal() const;

    //人所在的位置
    Pos man_pos;
    //目标位置
    const PosVector goals;
    //只包含 wall floor box
    ElementsMatrix room;
    // box 的索引
    PosVector box_index;
};

bool operator == (const BoardParam &p1, const BoardParam &p2);

#endif // BOARDPARAM_H
