#include "board.h"
#include "board_api.h"
#include "roomslice.h"
#include "boxmover.h"
#include <QDebug>

void Board::setMatrix(const ElementsMatrix &m)
{
    param.set_matrix(m);
}

bool Board::move(Direction &d)
{
    return Board_API::man_move(param, d);
}

bool Board::is_done() const
{
    return  Board_API::is_done(param);
}

ElementsMatrix Board::to_matrix() const
{
    return Board_API::to_matrix(param);
}
