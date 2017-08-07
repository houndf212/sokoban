#include "boardgraph.h"
#include "dijkstra.h"
#include "xsb.h"
#include "debug_print.h"

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
    auto path = G::AStart_path(graph, start, goal);
    for (const auto &p : path.first) {
        print(p);
    }
}
