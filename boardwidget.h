#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include <QWidget>
#include "boardparam.h"
#include "imagesource.h"

class BoardWidget : public QWidget
{
public:
    explicit BoardWidget(QWidget *parent=nullptr);

    void setMatrix(const ElementsMatrix &m);
    BoardParam getBoard() const { return board; }
    bool man_move(Direction d);
    bool is_done() const;
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    void createPixBuffer();
private:
    const ImageSource image;
    const int k_width;
    const int k_height;

    BoardParam board;
    QPixmap buffer_pix;
};

#endif // BOARDWIDGET_H
