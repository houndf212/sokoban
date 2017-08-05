#include "imagesource.h"

ImageSource::ImageSource()
{
    QPixmap all(":/elements.png");

    p_size = QSize(20, 20);

    p_man = all.copy(QRect(20, 0, 20, 20));
    p_wall = all.copy(QRect(0, 40, 20, 20));
    p_box = all.copy(QRect(40, 0, 20, 20));
    p_floor = all.copy(QRect(0, 0, 20, 20));
    p_goal = all.copy(QRect(0, 20, 20, 20));
    p_man_goal = all.copy(QRect(20, 20, 20, 20));
    p_box_goal = all.copy(QRect(60, 0, 20, 20));
}

QPixmap ImageSource::get_image(Elements e) const
{
    switch (e) {
    case Elements::man:
        return p_man;

    case Elements::wall:
        return p_wall;

    case Elements::box:
        return p_box;

    case Elements::floor:
        return p_floor;

    case Elements::goal:
        return p_goal;

    case Elements::man_goal:
        return p_man_goal;

    case Elements::box_goal:
        return p_box_goal;
    }
    assert(false);
    return QPixmap(20, 20);
}
