﻿#include <QApplication>
#include "boardwidget.h"
#include "xsb.h"
#include "boardparam.h"
#include "gamewindow.h"

void test()
{
    extern void test_print();
    extern void test_console_board();
    extern void test_boxmover();
    extern void test_assignmentproblem();
    extern void test_baordgraph();
    extern void test_matrixgraph();
//    test_baordgraph();
}

int main(int argc, char *argv[])
{
//    test();
//    return 0;
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
