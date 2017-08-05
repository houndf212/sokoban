#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <list>

#include "basic_pos.h"
#include "basic_resize_matrix.h"
#include "elements.h"
#include "movedirection.h"

typedef int type_value;
typedef int type_size;

typedef Basic_Pos<type_size> Pos;
typedef Basic_Resize_Matrix<type_value, type_size> IntMatrix;
typedef Basic_Resize_Matrix<Elements, type_size> ElementsMatrix;

typedef std::vector<Pos> PosVector;
typedef std::list<Pos> PosList;

#endif // TYPES_H
