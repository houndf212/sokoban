#include <QApplication>
#include "types.h"
#include "debug_print.h"

void test()
{
    extern void test_print();
    extern void test_console_board();
    test_console_board();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test();
//    return a.exec();


    return 0;
}
