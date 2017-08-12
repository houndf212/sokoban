#include "gamewindow.h"
#include "xsb.h"
#include "boardgraph.h"
#include "dijkstra.h"

GameWindow::GameWindow()
{
    board = new BoardWidget;
    cmb = new QComboBox;
    btn_solve = new QPushButton("auto solve");
    timer = new QTimer(this);

    connect(cmb, &QComboBox::currentTextChanged, this, &GameWindow::onComboChange);

    connect(btn_solve, &QPushButton::clicked, this, &GameWindow::onAutoSolve);

    connect(timer, &QTimer::timeout, this, &GameWindow::onTimeout);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(cmb);
    hlayout->addWidget(btn_solve);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(hlayout);
    layout->addWidget(board);

    setLayout(layout);

    initShortcut();
    loadCombo();
    onComboChange(cmb->currentText());
}

void GameWindow::initShortcut()
{
    {
        QAction *act = new QAction;
        connect(act, &QAction::triggered,
                [this](){ human_move(Direction::up);});
        act->setShortcut(Qt::Key_Up);
        addAction(act);
    }

    {
        QAction *act = new QAction;
        connect(act, &QAction::triggered,
                [this](){human_move(Direction::down);});
        act->setShortcut(Qt::Key_Down);
        addAction(act);
    }

    {
        QAction *act = new QAction;
        connect(act, &QAction::triggered,
                [this](){human_move(Direction::left);});
        act->setShortcut(Qt::Key_Left);
        addAction(act);
    }

    {
        QAction *act = new QAction;
        connect(act, &QAction::triggered,
                [this](){human_move(Direction::right);});
        act->setShortcut(Qt::Key_Right);
        addAction(act);
    }

}

void GameWindow::loadCombo()
{
    QSignalBlocker block(cmb);

    const QString str = ":/games/m%1.xsb";

    int i=1;
    while(true) {
        QString filename = str.arg(i++);
        if (!QFile::exists(filename))
            break;

        ElementsMatrix em = XSB::from_file(filename.toStdString().c_str());
        cmb->addItem(filename);
        board_map.emplace(filename, em);
    }
}

void GameWindow::human_move(Direction d)
{
    if (cmb->isEnabled())
        board->man_move(d);
}

void GameWindow::onAutoSolve()
{
    if (timer->isActive())
        leaveAutoSolve();
    else
        enterAutoSolve();
}

void GameWindow::onComboChange(const QString &txt)
{
    ElementsMatrix em = board_map.at(txt);
    board->setMatrix(em);
}

void GameWindow::onTimeout()
{
    if (mlst.empty()) {
        timer->stop();
        leaveAutoSolve();
        return;
    }
    Direction d = mlst.front();
    mlst.pop_front();
    bool b = board->man_move(d);
    assert(b==true);
}

void GameWindow::enterAutoSolve()
{
    if (board->is_done())
        return;

    btn_solve->setText("stop");
    cmb->setEnabled(false);

    typedef BoardGraph BG;
    typedef Dijkstra<BG> G;

    BG graph;
    auto start = board->getBoard();
    auto goal = start.to_goal();

    auto path = G::AStart_path(graph, start, goal);
    path.first.push_front(start);
    mlst = BG::trans_to(path.first);
    assert(start.can_solve(mlst));
    timer->start(400);
}

void GameWindow::leaveAutoSolve()
{
    btn_solve->setText("auto solve");
    cmb->setEnabled(true);
    mlst.clear();
    timer->stop();
}
