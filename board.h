#ifndef BOARD_H
#define BOARD_H
#include "types.h"

class Board
{
public:
    Board() = default;

    void setMatrix(const ElementsMatrix &m);

    bool move(Direction &d);
    bool is_done() const;

    ElementsMatrix to_matrix() const;

private:
    ElementsMatrix matrix;
    Pos man_pos;
    PosVector des_vec;
};

#endif // BOARD_H
