#include "consoleboard.h"
#include <QtCore>

Elements ConsoleBoard::to_element(char c)
{
    switch (c) {
    case '@':
        return Elements::Man;

    case '#':
        return Elements::Wall;

    case '$':
        return Elements::Box;

    case '.':
        return Elements::Destination;

    case '-':
        return Elements::Space;

    default:
        assert(false);
        break;
    }
    return Elements::Space;
}

char ConsoleBoard::to_char(Elements e)
{
    switch (e) {
    case Elements::Man:
        return '@';

    case Elements::Wall:
        return '#';

    case Elements::Box:
        return '$';

    case Elements::Destination:
        return '.';

    case Elements::Space:
        return '-';
    default:
        assert(false);
        break;
    }
    return '-';
}

//http://sokoban.cn/sokoplayer/SokoPlayer_HTML5.php
ElementsMatrix ConsoleBoard::from_file(const char *str)
{
    ElementsMatrix em;
    QFile file(str);
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
        col_size = qMax(col_size, lst.at(i).size());
    }
    int row_size = lst.size();

    em.resize(row_size, col_size);
    em.fill(Elements::Space);

    for (int row=0; row<row_size; ++row) {
        const auto &line = lst.at(row);
        for (int col=0; col<line.size(); ++col) {
            Pos p(row, col);
            char c = line.at(col);
            auto e = ConsoleBoard::to_element(c);
            em.set(p, e);
        }
    }

    return em;
}
