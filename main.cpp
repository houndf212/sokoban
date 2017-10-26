#include <QApplication>
#include "boardwidget.h"
#include "xsb.h"
#include "boardparam.h"
#include "gamewindow.h"

bool check()
{
    extern bool check_matrix_iterator();
    assert(check_matrix_iterator());
    return true;
}

void test()
{
    extern void test_print();
    extern void test_console_board();
    extern void test_boxmover();
    extern void test_assignmentproblem();
    extern void test_baordgraph();
    extern void test_matrixgraph();
    extern void test_munkres();
    extern void test_HungarianAlg();
    extern void test_matrix_iterator();
    extern void test_matrix_resize();

//    test_matrix_resize();
}

int main(int argc, char *argv[])
{
//    assert(check());
//    test();
//    return 0;
    QApplication a(argc, argv);

    GameWindow w;
    w.show();

    return a.exec();
}
