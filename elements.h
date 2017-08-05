#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <assert.h>

typedef unsigned char Elements_t;
enum class Elements : Elements_t
{
    man = 1<<3,  //1000
    wall = 1, //0001
    box = 1<<2,  //0100
    floor = 1<<1,//0010
    goal = wall|floor, //0011

    man_goal = man|goal, // 1011
    box_goal = box|goal, // 0111
};

template<Elements e>
constexpr Elements_t toInt()
{
    return static_cast<Elements_t>(e);
}

inline Elements add_goal(Elements e)
{
    assert(e != Elements::wall);
    static_assert((toInt<Elements::man>()|toInt<Elements::goal>()) == toInt<Elements::man_goal>(),"");
    static_assert((toInt<Elements::box>()|toInt<Elements::goal>()) == toInt<Elements::box_goal>(),"");
    static_assert((toInt<Elements::wall>()|toInt<Elements::goal>()) == toInt<Elements::goal>(),"");
    static_assert((toInt<Elements::floor>()|toInt<Elements::goal>()) == toInt<Elements::goal>(),"");
    return Elements(Elements_t(e)|toInt<Elements::goal>());
}

#endif // ELEMENTS_H
