#include "boxmover.h"
#include "xsb.h"
#include "board_api.h"
#include "debug_print.h"
#include <QDebug>

void test_boxmover()
{
    ElementsMatrix m = XSB::from_file("board.xsb");
    BoardParam param;
    param.set_matrix(m);
    print(param);
    qDebug() << BoxMover::can_box_move(Pos(2, 6), Direction::down, param);
    qDebug() << BoxMover::can_box_move(Pos(2, 6), Direction::up, param);

    qDebug() << BoxMover::can_box_move(Pos(2, 5), Direction::up, param);
    qDebug() << BoxMover::can_box_move(Pos(3, 5), Direction::left, param);
    qDebug() << BoxMover::can_box_move(Pos(3, 5), Direction::right, param);

    auto lst = BoxMover::next_move(param);
    for (const auto &p : lst) {
        print(p);
    }
    BoardParam param1 = lst.front();
    auto list1 = BoxMover::next_move(param1);
    for (const auto &p : list1) {
        print(p);
    }

    BoardParam param2 = list1.front();
    auto list2 = BoxMover::next_move(param2);
    for (const auto &p : list2) {
        print(p);
    }

    BoardParam param3 = list2.front();
    auto list3 = BoxMover::next_move(param3);
    for (const auto &p : list3) {
        print(p);
    }
}
