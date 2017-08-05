#include <QApplication>
#include "boardwidget.h"
#include "xsb.h"
#include "debug_print.h"

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

    BoardWidget w;
    w.setMatrix(m);
    w.show();
    return a.exec();
}
