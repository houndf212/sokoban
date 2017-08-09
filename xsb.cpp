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
        for (auto col=em.szero(); col<line.size(); ++col) {
            Pos p(row, col);
            char c = line.at(col);
            auto e = XSB::char_to_e(c);
            em.set(p, e);
        }
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
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            auto e = m.get(p);
            auto c = e_to_char(e);
            str.push_back(c);
        }
        str.push_back('\n');
    }
    return str;
}


void XSB::replace_outer_floor(ElementsMatrix &m)
{
    //保证所有的room都是被wall包裹的
    //四个方向 从上到下从下倒上，从左到右，从右到左

    auto test_set = [&](Pos p) {
        assert(m.isInMatrix(p));
        if (m.get(p) != Elements::wall) {
            //这里说明room不是被墙包裹的
            assert(m.get(p) == Elements::floor);
            m.set(p, Elements::wall);
            return false;
        }
        return true;
    };

    for (auto row=m.szero(); row<m.row_size(); ++row) {
        //从左到右
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            if (test_set(Pos(row, col)))
                break;
        }
        //从右到左
        for (auto col=m.col_size()-1; col>=m.szero(); --col) {
            if (test_set(Pos(row, col)))
                break;
        }
    }

    for (auto col=m.szero(); col<m.col_size(); ++col) {

        //从上到下
        for (auto row=m.szero(); row<m.row_size(); ++row) {
            if (test_set(Pos(row, col)))
                break;
        }
        //从下到上
        for (auto row=m.row_size()-1; row>=m.szero(); --row) {
            if (test_set(Pos(row, col)))
                break;
        }
    }
}

static bool is_wall_row(type_size row, const ElementsMatrix &m)
{
    assert(row<m.row_size());
    for (auto col=m.szero(); col<m.col_size(); ++col) {
        if (m.get(Pos(row, col)) != Elements::wall)
            return false;
    }
    return true;
}

static bool is_wall_col(type_size col, const ElementsMatrix &m)
{
    assert(col<m.col_size());
    for (auto row=m.szero(); row<m.row_size(); ++row) {
        if (m.get(Pos(row, col)) != Elements::wall)
            return false;
    }
    return true;
}

static ElementsMatrix remove_row(type_size row, const ElementsMatrix &m)
{
    ElementsMatrix em;
    em.resize(m.row_size()-1, m.col_size());

    for (auto r=m.szero(); r<m.row_size(); ++r) {
        if (r == row) continue;
        auto r_to = r<row ? r : r-1;
        for (auto c=m.szero(); c<m.col_size(); ++c) {
            Pos from(r, c);
            Pos to(r_to, c);
            em.set(to, m.get(from));
        }
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
        for (auto r=m.szero(); c<m.row_size(); ++r) {
            Pos from(r, c);
            Pos to(r, c_to);
            em.set(to, m.get(from));
        }
    }
    return em;
}

ElementsMatrix XSB::remove_outer_wall(ElementsMatrix m)
{
    for (auto row=m.szero(); row<m.row_size()-1;) {
        if (is_wall_row(row, m) && is_wall_row(row+1, m)) {
            m = remove_row(row, m);
        }
        else
            row++;
    }

    for (auto col=m.szero(); col<m.col_size()-1;) {
        if (is_wall_col(col, m) && is_wall_col(col+1, m)) {
            m = remove_col(col, m);
        }
        else
            col++;
    }

    return m;
}
