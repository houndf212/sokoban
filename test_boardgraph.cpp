#include "boardgraph.h"
#include "dijkstra.h"
#include "xsb.h"
#include "debug_print.h"
#include <QtCore>

void test_baordgraph()
{
    ElementsMatrix m = XSB::from_file("board.xsb");
    BoardParam start;
    start.set_matrix(m);
    print(start);

    BoardParam goal = start.to_goal();
    print(goal);

    typedef BoardGraph BG;
    typedef Dijkstra<BG> G;
    BG graph;

    {
        QElapsedTimer timer;
        timer.start();
        auto path = G::shortest_path(graph, start, goal);
        assert(!path.first.empty());
        qDebug() << timer.elapsed();
        qDebug()<< "move size: "<<path.second;
    }


    {
        QElapsedTimer timer;
        timer.start();
        auto path = G::AStart_path(graph, start, goal);
        assert(!path.first.empty());
        qDebug() << timer.elapsed();
        qDebug()<< "move size: "<<path.second;
    }
}
