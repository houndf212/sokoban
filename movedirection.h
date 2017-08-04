#ifndef MOVEDIRECTION_H
#define MOVEDIRECTION_H
#include <assert.h>

typedef unsigned char Direction_t;
enum class Direction : Direction_t
{
    NotValid,
    up = 0x1 | 0x1 <<1, // 0011
    down = up<<2, // 1100
    left = 0x1 | 0x1<<2, // 0101
    right = left<<1, //1010

    push = 0x1 << 4,
    push_up = push | up,
    push_down = push | down,
    push_left = push | left,
    push_right = push | right,
};

template<Direction d>
constexpr Direction_t toInt()
{
    return static_cast<Direction_t>(d);
}

inline Direction_t toInt(Direction d)
{
    return static_cast<Direction_t>(d);
}

inline bool is_reverse(Direction d1, Direction d2)
{
    static_assert((toInt<Direction::up>()&toInt<Direction::down>()) == 0, "");
    static_assert((toInt<Direction::left>()&toInt<Direction::right>()) == 0, "");

    static_assert((toInt<Direction::up>()&toInt<Direction::right>()) != 0, "");
    static_assert((toInt<Direction::up>()&toInt<Direction::left>()) != 0, "");

    static_assert((toInt<Direction::down>()&toInt<Direction::right>()) != 0, "");
    static_assert((toInt<Direction::down>()&toInt<Direction::left>()) != 0, "");

    return (toInt(d1)&toInt(d2)) == 0;
}

inline Direction reverse(Direction d)
{
    assert(d!=Direction::NotValid);
    constexpr Direction_t full = toInt<Direction::up>() | toInt<Direction::down>();

    static_assert((full^toInt<Direction::up>()) == toInt<Direction::down>(), "");
    static_assert((full^toInt<Direction::down>()) == toInt<Direction::up>(), "");
    static_assert((full^toInt<Direction::right>()) == toInt<Direction::left>(), "");
    static_assert((full^toInt<Direction::left>()) == toInt<Direction::right>(), "");

    return Direction(toInt(d)^full);
}

inline bool is_push(Direction d)
{
    return (toInt(d) & toInt<Direction::push>()) == toInt<Direction::push>();
}

inline Direction add_push(Direction d)
{
    assert(d != Direction::NotValid);
    return Direction(toInt(d) | toInt<Direction::push>());
}
#endif // MOVEDIRECTION_H
