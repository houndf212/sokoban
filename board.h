#ifndef BOARD_H
#define BOARD_H
#include "types.h"

class Board
{
public:
    Board(const ElementsMatrix &em);

    bool isDone() const;
    bool move(Direction d);


    // matrix api
    bool isInBoard(Pos p) const { return m_matrix.isInMatrix(p); }
private:
    ElementsMatrix m_matrix;
};

#endif // BOARD_H
