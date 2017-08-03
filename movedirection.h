#ifndef MOVEDIRECTION_H
#define MOVEDIRECTION_H
#include <assert.h>

enum class Direction
{
    NotValid,
    up = 0x1 | 0x1 <<1, // 0011
    down = up<<2, // 1100
    left = 0x1 | 0x1<<2, // 0101
    right = left<<1, //1010
};

template<Direction d>
constexpr int toInt()
{
    return static_cast<int>(d);
}

inline bool is_reverse(Direction d1, Direction d2)
{
    static_assert((toInt<Direction::up>()&toInt<Direction::down>()) == 0, "");
    static_assert((toInt<Direction::left>()&toInt<Direction::right>()) == 0, "");

    static_assert((toInt<Direction::up>()&toInt<Direction::right>()) != 0, "");
    static_assert((toInt<Direction::up>()&toInt<Direction::left>()) != 0, "");

    static_assert((toInt<Direction::down>()&toInt<Direction::right>()) != 0, "");
    static_assert((toInt<Direction::down>()&toInt<Direction::left>()) != 0, "");

    return (static_cast<int>(d1)&static_cast<int>(d2)) == 0;
}

inline Direction reverse(Direction d)
{
    assert(d!=Direction::NotValid);
    constexpr int full = toInt<Direction::up>() | toInt<Direction::down>();

    static_assert((full^toInt<Direction::up>()) == toInt<Direction::down>(), "");
    static_assert((full^toInt<Direction::down>()) == toInt<Direction::up>(), "");
    static_assert((full^toInt<Direction::right>()) == toInt<Direction::left>(), "");
    static_assert((full^toInt<Direction::left>()) == toInt<Direction::right>(), "");

    return Direction(static_cast<int>(d)^full);
}
#endif // MOVEDIRECTION_H
