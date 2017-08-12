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
    setFixedSize(buffer_pix.size());
    createPixBuffer();
}

bool BoardWidget::man_move(Direction d)
{
    bool b = board.man_move(d);
    if (b) {
        createPixBuffer();
    }
    return b;
}

bool BoardWidget::is_done() const
{
    return board.is_done();
}

void BoardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setWindow(0, 0, buffer_pix.width(), buffer_pix.height());
    painter.drawPixmap(0, 0, buffer_pix);
}

void BoardWidget::createPixBuffer()
{
    auto matrix = board.to_matrix();

    QPainter painter(&buffer_pix);
    for (auto row=matrix.szero(); row<matrix.row_size(); ++row) {
        for (auto col=matrix.szero(); col<matrix.col_size(); ++col) {
            Pos p(row, col);
            QPixmap pix = image.get_image(matrix.get(p));
            painter.drawPixmap(k_width*col,
                               k_height*row,
                               pix);
        }
    }
    update();
}


