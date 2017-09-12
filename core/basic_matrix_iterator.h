#ifndef BASIC_MATRIX_ITERATOR_H
#define BASIC_MATRIX_ITERATOR_H
#include "basic_pos.h"

template<typename M>
class Basic_Position
{
public:
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;

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
public:
    typedef reference reference_type;
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;

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
        return position.matrix->iter_ref(position.pos);
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
public:
    typedef reference reference_type;
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;

    Basic_Matrix_Row_Iterator(M *m, size_type row, size_type col)
        :position(m, row, col)
    {}

    Basic_Pos<size_type> pos() const
    {
        return position.pos;
    }

    reference operator*() const
    {
        return position.matrix->iter_ref(position.pos);
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
public:
    typedef reference reference_type;
    typedef typename M::value_type value_type;
    typedef typename M::size_type size_type;

    Basic_Matrix_Col_Iterator(M *m, size_type row, size_type col)
        :position(m, row, col)
    {}

    Basic_Pos<size_type> pos() const
    {
        return position.pos;
    }

    reference operator*() const
    {
        return position.matrix->iter_ref(position.pos);
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
class IteratorRange
{

public:
    IteratorRange(const T &a, const T& b)
        : m_begin(a), m_end(b)
    {}
    Basic_Pos<typename T::size_type> pos() const
    {
        return m_begin.pos();
    }

    typename T::size_type row() const
    {
        return  m_begin.pos().row();
    }

    typename T::size_type col() const
    {
        return  m_begin.pos().col();
    }

    operator bool() const
    {
        return m_begin != m_end;
    }

    void operator ++()
    {
        ++m_begin;
    }

    void next()
    {
        ++m_begin;
    }

    typename T::reference_type operator *() const
    {
        return *m_begin;
    }

    //为了 实现 for (auto &v : m.range([0]));
    T begin() const { return m_begin; }
    T end() const { return m_end; }

private:
    T m_begin;
    const T m_end;
};

#endif // BASIC_MATRIX_ITERATOR_H
