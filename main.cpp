#include <QApplication>
#include "types.h"
#include "debug_print.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    return a.exec();
    Pos p(1, 2);
    print(p);

    return 0;
}
