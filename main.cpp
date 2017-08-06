#include <QApplication>
#include "boardwidget.h"
#include "xsb.h"
#include "debug_print.h"
#include "boardparam.h"

void test()
{
    extern void test_print();
    extern void test_console_board();
    test_console_board();
}

int main(int argc, char *argv[])
{
    //    test();
    QApplication a(argc, argv);

    ElementsMatrix m = XSB::from_file("board.xsb");
    BoardParam param;
    param.set_matrix(m);

    BoardWidget w;
    w.setMatrix(m);
    w.show();
    return a.exec();
}
