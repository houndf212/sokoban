#ifndef BOARDPARAM_H
#define BOARDPARAM_H
#include <memory>
#include "types.h"
#include "movelist.h"


//这个类描述一个推箱子所有需要的元素，在boardapi操作这个类

class BoardParam
{
public:
    //初始化函数
    void set_matrix(const ElementsMatrix &m);

    //唯一操作推箱子接口
    bool man_move(Direction &d);

    //内部数据read  readonly
    const Pos &man() const { return man_pos; }

    size_t goals_size() const
    {
        assert(m_goals!=nullptr);
        return m_goals->size();
    }
    const PosVector *goals() const
    {
        return m_goals.get();
    }
    const PosVector &boxes() const { return box_index; }

    const ElementsMatrix &room() const { return m_room; }

    //测试函数
    bool is_done() const;
    bool is_goal(Pos p) const;
    bool is_absolutely_dead_box(Pos box) const;
    bool is_absolutely_dead() const;
    bool can_solve(const MoveList &mlst) const;

    //用于自动推箱子
    std::list<BoardParam> next_move() const;

    //转化函数
    ElementsMatrix to_matrix() const;
    BoardParam to_goal() const;
private:
    void box_move(Pos box, Pos to);
    bool can_box_move(Pos box, Direction d) const;
private:
    //暂时未使用的函数
    bool precise_equal(const BoardParam &param) const;
    bool like_equal(const BoardParam &param) const;
private:
    //人所在的位置
    Pos man_pos;
    //目标位置
    std::shared_ptr<PosVector> m_goals;
    //只包含 wall floor box
    ElementsMatrix m_room;
    // box 的索引
    PosVector box_index;
};

bool operator == (const BoardParam &p1, const BoardParam &p2);

#endif // BOARDPARAM_H
