#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <list>


#include "basic_pos.h"
#include "basic_resize_matrix.h"
#include "elements.h"
#include "movedirection.h"

typedef int value_type;
typedef int size_type;

typedef Basic_Pos<size_type> Pos;
typedef Basic_Resize_Matrix<value_type, size_type> IntMatrix;
typedef Basic_Resize_Matrix<Elements, size_type> ElementsMatrix;

typedef std::vector<Pos> PosVector;
typedef std::list<Pos> PosList;

#endif // TYPES_H
