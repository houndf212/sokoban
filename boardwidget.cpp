#include "boardwidget.h"
#include <QPainter>
#include <QKeyEvent>

BoardWidget::BoardWidget(QWidget *parent)
    :QWidget(parent)
    ,k_width(image.size().width())
    ,k_height(image.size().height())
{
}

void BoardWidget::setMatrix(const ElementsMatrix &m)
{
    board.set_matrix(m);
    buffer_pix = QPixmap(m.col_size()*k_width, m.row_size()*k_height);
    resize(buffer_pix.size());
    createPixBuffer();
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setWindow(0, 0, buffer_pix.width(), buffer_pix.height());
    painter.drawPixmap(0, 0, buffer_pix);
}

void BoardWidget::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();

    Direction d = Direction::NotValid;
    switch (key) {
    case Qt::Key_Left:
        d = Direction::left;
        break;
    case Qt::Key_Right:
        d = Direction::right;
        break;
    case Qt::Key_Up:
        d = Direction::up;
        break;
    case Qt::Key_Down:
        d = Direction::down;
        break;
    default:
        return;
        break;
    }
    bool b = board.man_move(d);
    if (b) {
        createPixBuffer();
    }
}

void BoardWidget::createPixBuffer()
{
    auto matrix = board.to_matrix();

    QPainter painter(&buffer_pix);
    for (auto row=matrix.zero(); row<matrix.row_size(); ++row) {
        for (auto col=matrix.zero(); col<matrix.col_size(); ++col) {
            Pos p(row, col);
            QPixmap pix = image.get_image(matrix.get(p));
            painter.drawPixmap(k_width*col,
                               k_height*row,
                               pix);
        }
    }
    update();
}


