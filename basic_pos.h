#ifndef BASIC_POS_H
#define BASIC_POS_H
#include <cstdlib>

template <typename T>
class Basic_Pos
{
public:
    typedef T value_type;

    Basic_Pos(T x=0, T y=0) : m_x(x), m_y(y) {}

    const T& x() const { return m_x; }
    const T& y() const { return m_y; }

    T& x() { return m_x; }
    T& y() { return m_y; }

    bool equal(const Basic_Pos& p) const
    {
        return x() == p.x() && y() == p.y();
    }
private:
    T m_x;
    T m_y;
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
    return std::abs(p1.x()-p2.x())+std::abs(p1.y()-p2.y());
}

#endif // BASIC_POS_H
