#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <list>


#include "basic_pos.h"
#include "basic_resize_matrix.h"
#include "elements.h"
#include "movedirection.h"

typedef Basic_Pos<int> Pos;
typedef Basic_Resize_Matrix<int, int> IntMatrix;
typedef Basic_Resize_Matrix<Elements, int> ElementsMatrix;

typedef std::vector<Pos> PosVector;
typedef std::list<Pos> PosList;

#endif // TYPES_H
