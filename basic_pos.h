﻿#ifndef BASIC_POS_H
#define BASIC_POS_H
#include <cstdlib>
#include "movedirection.h"

template <typename T>
class Basic_Pos
{
public:
    typedef T value_type;

    Basic_Pos() = default;
    Basic_Pos(T row, T col) : m_row(row), m_col(col) {}

    const T& row() const { return m_row; }
    const T& col() const { return m_col; }

    T& row() { return m_row; }
    T& col() { return m_col; }

    bool equal(const Basic_Pos& p) const
    {
        return row() == p.row() && col() == p.col();
    }

    Basic_Pos move(Direction d) const
    {
        Basic_Pos to = *this;
        switch (d) {
        case Direction::up:
            to.row()--;
            break;
        case Direction::down:
            to.row()++;
            break;
        case Direction::left:
            to.col()--;
            break;
        case Direction::right:
            to.col()++;
            break;
        default:
            assert(false);
            break;
        }
        return to;
    }
private:
    T m_row;
    T m_col;
};

template<class T>
inline bool operator==(const Basic_Pos<T> &p1, const Basic_Pos<T> &p2)
{
    return p1.equal(p2);
}

template<class T>
inline bool operator!=(const Basic_Pos<T> &p1, const Basic_Pos<T> &p2)
{
    return !p1.equal(p2);
}

template<class T>
inline T Manhattan_Distance(const Basic_Pos<T> &p1, const Basic_Pos<T> &p2)
{
    return std::abs(p1.row()-p2.row())+std::abs(p1.col()-p2.col());
}

#endif // BASIC_POS_H
