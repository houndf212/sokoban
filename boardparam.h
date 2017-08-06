#ifndef BOARDPARAM_H
#define BOARDPARAM_H
#include "types.h"

//这个类描述一个推箱子所有需要的元素，在boardapi操作这个类

class BoardParam
{
public:
    void set_matrix(const ElementsMatrix &m);

    bool is_goal(Pos p) const;

    //人所在的位置
    Pos man_pos;
    //目标位置
    const PosVector goals;
    //只包含 wall floor box
    ElementsMatrix room;
    // box 的索引
    PosVector box_index;
};

#endif // BOARDPARAM_H
