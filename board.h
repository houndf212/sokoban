#ifndef BOARD_H
#define BOARD_H
#include "boardparam.h"

// board is a wapper for boardparam
class Board
{
public:
    void setMatrix(const ElementsMatrix &m);

    bool move(Direction &d);

    bool is_done() const;

    ElementsMatrix to_matrix() const;

private:
    BoardParam param;
};

#endif // BOARD_H
