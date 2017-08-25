#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QtWidgets>
#include "boardwidget.h"
#include "movelist.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();
private:
    void initShortcut();
    void loadCombo();
    void human_move(Direction d);

    Q_SLOT void onAutoSolve();
    Q_SLOT void onComboChange(const QString &txt);
    Q_SLOT void onTimeout();

    void enterAutoSolve();
    void leaveAutoSolve();
private:
    BoardWidget *board;
    QComboBox *cmb;
    QPushButton *btn_solve;

    std::map<QString, ElementsMatrix> board_map;

    MoveList mlst;
    QTimer *timer;
};

#endif // GAMEWINDOW_H
