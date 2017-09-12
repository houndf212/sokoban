#ifndef BASIC_MATRIX_ITERATOR_H
#define BASIC_MATRIX_ITERATOR_H
#include "basic_pos.h"

template<typename M>
class Basic_Position
{
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;
public:
    Basic_Position(M *m, size_type row, size_type col)
        :matrix(m), pos(row, col)
    {}

    bool operator !=(const Basic_Position &right) const
    {
        assert(matrix == right.matrix);
        return  pos != right.pos;
    }

    M* matrix;
    Basic_Pos<size_type> pos;
};

template<class M, class reference>
class Basic_Matrix_Iterator
{
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;
public:
    Basic_Matrix_Iterator(M *m, size_type row, size_type col)
        :position(m, row, col)
    {}

    Basic_Pos<size_type> pos() const
    {
        return position.pos;
    }

    bool operator !=(const Basic_Matrix_Iterator &right) const
    {
        return  position != right.position;
    }

    reference operator*() const
    {
        return position.matrix->m[position.pos.row()][position.pos.col()];
    }

    Basic_Matrix_Iterator& operator++()
    {
        position.pos.col()++;
        position.pos.row() += position.pos.col() / position.matrix->col_size();
        position.pos.col() %= position.matrix->col_size();
        return *this;
    }
private:
    Basic_Position<M> position;
};

template<class M, class reference>
class Basic_Matrix_Row_Iterator
{
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;
public:
    Basic_Matrix_Row_Iterator(M *m, size_type row, size_type col)
        :position(m, row, col)
    {}

    Basic_Pos<size_type> pos() const
    {
        return position.pos;
    }

    reference operator*() const
    {
        return position.matrix->m[position.pos.row()][position.pos.col()];
    }

    bool operator !=(const Basic_Matrix_Row_Iterator &right) const
    {
        return  position != right.position;
    }

    Basic_Matrix_Row_Iterator& operator++()
    {
        position.pos.col()++;
        return *this;
    }
private:
    Basic_Position<M> position;
};

template<class M, class reference>
class Basic_Matrix_Col_Iterator
{
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;
public:
    Basic_Matrix_Col_Iterator(M *m, size_type row, size_type col)
        :position(m, row, col)
    {}

    Basic_Pos<size_type> pos() const
    {
        return position.pos;
    }

    reference operator*() const
    {
        return position.matrix->m[position.pos.row()][position.pos.col()];
    }

    bool operator !=(const Basic_Matrix_Col_Iterator &right) const
    {
        return  position != right.position;
    }

    Basic_Matrix_Col_Iterator& operator++()
    {
        position.pos.row()++;
        return *this;
    }
private:
    Basic_Position<M> position;
};

template <typename T>
struct IteratorRange
{
    const T begin;
    const T end;
};

#endif // BASIC_MATRIX_ITERATOR_H
