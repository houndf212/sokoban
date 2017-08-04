#ifndef BOARD_API_H
#define BOARD_API_H
#include "types.h"

class Board_API
{
public:
    static void swap_pos(ElementsMatrix *m, Pos p1, Pos p2);
    static void move(Pos *p, Direction d);
};

#endif // BOARD_API_H
