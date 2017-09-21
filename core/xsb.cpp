#include "xsb.h"
#include <QtCore>

char XSB::e_to_char(Elements e)
{
    switch (e) {
    case Elements::man:
        return '@';
    case Elements::man_goal:
        return '+';
    case Elements::box:
        return '$';
    case Elements::box_goal:
        return '*';
    case Elements::wall:
        return '#';
    case Elements::goal:
        return '.';
    case Elements::floor:
        return '-';
    }
    assert(false);
    return '-';
}

Elements XSB::char_to_e(char c)
{
    switch (c) {
    case '@':
        return Elements::man;
    case '+':
        return Elements::man_goal;
    case '$':
        return Elements::box;
    case '*':
        return Elements::box_goal;
    case '#':
        return Elements::wall;
    case '.':
        return Elements::goal;
    case ' ':
    case '-':
    case '_':
        return Elements::floor;
    default:
        assert(false);
        break;
    }
    return Elements::floor;
}

ElementsMatrix XSB::from_file(const char *filestr)
{
    ElementsMatrix em;
    QFile file(filestr);
    bool b = file.open(QFile::ReadOnly);
    if (!b)
        return em;

    QByteArray arr = file.readAll();
    arr = arr.trimmed();
    QByteArrayList lst = arr.split('\n');
    if (lst.isEmpty())
        return em;

    auto col_size = em.szero();
    for (auto i=em.szero(); i<lst.size(); ++i) {
        lst[i] = lst[i].trimmed();
        col_size = std::max(col_size, type_size(lst.at(i).size()));
    }
    type_size row_size = lst.size();

    em.resize(row_size, col_size);
    em.fill(Elements::floor);

    for (auto row=em.szero(); row<row_size; ++row) {
        const auto &line = lst.at(row);
        std::transform(line.begin(), line.end(), em.row_begin(row), char_to_e);
    }
    replace_outer_floor(em);
    return remove_outer_wall(em);
}

char XSB::d_to_char(Direction d)
{
    assert(d!=Direction::NotValid);
    switch (d) {
    case Direction::push:
    case Direction::NotValid:
        break;

    case Direction::up:
        return 'u';
    case Direction::push_up:
        return 'U';

    case Direction::down:
        return 'd';
    case Direction::push_down:
        return 'D';

    case Direction::left:
        return 'l';
    case Direction::push_left:
        return 'L';

    case Direction::right:
        return 'r';
    case Direction::push_right:
        return 'R';
    }

    assert(false);
    return '*';
}

Direction XSB::char_to_d(char c)
{
    switch (c) {
    case 'u':
        return Direction::up;
    case 'U':
        return Direction::push_up;

    case 'd':
        return Direction::down;
    case 'D':
        return Direction::push_down;

    case 'l':
        return Direction::left;
    case 'L':
        return Direction::push_left;

    case 'r':
        return Direction::right;
    case 'R':
        return Direction::push_right;
    default:
        break;
    }
    assert(false);
    return Direction::NotValid;
}

std::string XSB::to_string(const ElementsMatrix &m)
{
    std::string str;
    for (auto row=m.szero(); row<m.row_size(); ++row) {
        std::transform(m.row_begin(row), m.row_end(row), std::back_inserter(str), e_to_char);
        str.push_back('\n');
    }
    return str;
}

template <class R>
static void test_set_range(const R &range)
{
    for (auto &v : range) {
        if (v != Elements::wall) {
            //这里说明room不是被墙包裹的
            assert(v == Elements::floor);
            v = Elements::wall;
        }
        else
            break;
    }
}

void XSB::replace_outer_floor(ElementsMatrix &m)
{
    //保证所有的room都是被wall包裹的
    //四个方向 从上到下从下倒上，从左到右，从右到左
    for (auto row=m.szero(); row<m.row_size(); ++row) {
        test_set_range(m.row_range(row));
        test_set_range(m.row_reverse_range(row));
    }

    for (auto col=m.szero(); col<m.col_size(); ++col) {
        test_set_range(m.col_range(col));
        test_set_range(m.col_reverse_range(col));
    }
}

template <class R>
static bool is_wall_range(const R &range)
{
    auto equal_wall = [](Elements e) { return e == Elements::wall; };
    return std::all_of(range.begin(), range.end(), equal_wall);
}

static ElementsMatrix remove_row(type_size row, const ElementsMatrix &m)
{
    ElementsMatrix em;
    em.resize(m.row_size()-1, m.col_size());

    for (auto r=m.szero(); r<m.row_size(); ++r) {
        if (r == row) continue;
        auto r_to = r<row ? r : r-1;
        std::copy(m.row_begin(r), m.row_end(r), em.row_begin(r_to));
    }
    return em;
}

static ElementsMatrix remove_col(type_size col, const ElementsMatrix &m)
{
    ElementsMatrix em;
    em.resize(m.row_size(), m.col_size()-1);

    for (auto c=m.szero(); c<m.col_size(); ++c) {
        if (c == col) continue;
        auto c_to = c<col ? c : c-1;
        std::copy(m.col_begin(c), m.col_end(c), em.col_begin(c_to));
    }
    return em;
}

ElementsMatrix XSB::remove_outer_wall(ElementsMatrix m)
{
    for (auto row=m.szero(); row<m.row_size()-1;) {
        if (is_wall_range(m.row_range(row)) && is_wall_range(m.row_range(row+1))) {
            m = remove_row(row, m);
        }
        else
            row++;
    }

    for (auto col=m.szero(); col<m.col_size()-1;) {
        if (is_wall_range(m.col_range(col)) && is_wall_range(m.col_range(col+1))) {
            m = remove_col(col, m);
        }
        else
            col++;
    }

    return m;
}
