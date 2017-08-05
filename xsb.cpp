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

    int col_size = 0;
    for (int i=0; i<lst.size(); ++i) {
        lst[i] = lst[i].trimmed();
        col_size = qMax(col_size, lst.at(i).size());
    }
    int row_size = lst.size();

    em.resize(row_size, col_size);
    em.fill(Elements::floor);

    for (int row=0; row<row_size; ++row) {
        const auto &line = lst.at(row);
        for (int col=0; col<line.size(); ++col) {
            Pos p(row, col);
            char c = line.at(col);
            auto e = XSB::char_to_e(c);
            em.set(p, e);
        }
    }
    return em;
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
    for (auto row=m.zero(); row<m.row_size(); ++row) {
        for (auto col=m.zero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            auto e = m.get(p);
            auto c = e_to_char(e);
            str.push_back(c);
        }
        str.push_back('\n');
    }
    return str;
}

