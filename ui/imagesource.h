#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QPixmap>
#include "elements.h"

class ImageSource
{
public:
    ImageSource();
    const QSize &size() const { return p_size; }
    QPixmap get_image(Elements e) const;
private:
    QSize p_size;
    QPixmap p_man;
    QPixmap p_wall;
    QPixmap p_box;
    QPixmap p_floor;
    QPixmap p_goal;
    QPixmap p_man_goal;
    QPixmap p_box_goal;
};

#endif // IMAGESOURCE_H
