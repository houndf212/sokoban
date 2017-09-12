#include "boardgraph.h"
#include <string>
#include <queue>
#include "assignmentproblem.h"
#include "maskmatrix.h"
#include "matrixgraph.h"
#include "dijkstra.h"

size_t BoardGraph::BoardHash::operator()(const BoardParam &param) const
{
    const ElementsMatrix &m = param.room();
    std::string str;
    str.reserve(m.row_size()*m.col_size());

    for( auto &v : m) {
        str.push_back(static_cast<char>(v));
    }
    return std::hash<std::string>()(str);
}

MoveList BoardGraph::solve(const BoardGraph::vertex_t &start)
{
    typedef BoardGraph BG;
    typedef Dijkstra<BG> G;
    BG graph;

    auto path = G::AStart_path(graph, start, start.to_goal());
    path.first.push_front(start);
    auto mlst = trans_to(path.first);
    assert(start.can_solve(mlst));
    return mlst;
}

BoardGraph::VertexList BoardGraph::neighbors(const vertex_t &param)
{
    return param.next_move();
}

BoardGraph::distance_t BoardGraph::distance(const BoardGraph::vertex_t &v1, const BoardGraph::vertex_t &v2)
{
    Q_UNUSED(v1);
    Q_UNUSED(v2);
    return distance_t(1);
}

BoardGraph::distance_t BoardGraph::heuristic(const BoardGraph::vertex_t &v1, const BoardGraph::vertex_t &v2)
{
    //这个函数需要调整，当goal的数值过大的时候，这里的计算成为了瓶颈
    assert(v2.is_done());
    Q_UNUSED(v2);

    const auto size = v1.goals_size();
    IntMatrix m;
    m.resize(size, size);

    auto index = m.szero();
    for (auto box : v1.boxes()) {
        for (auto goal : v1.goals()) {
            distance_t d = Manhattan_Distance(box, goal);
            Pos p(index/size, index%size);
            m.set(p, d);
            index++;
        }
    }

    auto p = AssignmentProblem::min_assignment<distance_t>(m);
    return p.second;
}

BoardGraph::distance_t BoardGraph::greedy_search(const IntMatrix &m)
{
    //实现了 匈牙利算法,不需要贪婪搜索了
    assert(false);

    assert(m.row_size() == m.col_size());
    const auto size = m.row_size();
    MaskMatrix mask;
    mask.resize(m.size());
    mask.unmask_all();

    auto mask_p = [&mask](Pos p) {
        for(auto i=mask.szero(); i<mask.row_size(); ++i) {
            mask.mask(Pos(i, p.col()));
            mask.mask(Pos(p.row(), i));
        }
    };

    auto comp = [&m](const Pos &p1, const Pos &p2) {
        return m.get(p1)>m.get(p2);
    };

    PosVector pq;


    for (auto it=m.range(); it; ++it) {
        pq.push_back(it.pos());
        std::push_heap(begin(pq), end(pq), comp);
    }

    distance_t weight = 0;
    auto n = 1;
    while(n!=size) {
        std::pop_heap(begin(pq), end(pq), comp);
        Pos min = pq.back();
        pq.pop_back();

        if (mask.is_mask(min))
            continue;
        else {
            weight += m.get(min);
            mask_p(min);
            n++;
        }
    }
    return weight;
}

MoveList BoardGraph::trans_to(const BoardGraph::VertexList &ves)
{
    auto first = begin(ves);
    auto second = first;
    ++second;

    MoveList mlst;
    while(second != end(ves)) {
        auto m = to_movelist(*first, *second);
        mlst.check_append(m);
        ++first;
        ++second;
    }
    return mlst;
}

//计算两个 box move 之间的插值 v1 --> v2
MoveList BoardGraph::to_movelist(const BoardGraph::vertex_t &v1, const BoardGraph::vertex_t &v2)
{
    //先找到box 移动的位置
    Pos box1(-1, -1);
    for (auto p : v1.boxes()) {
        if (v2.room().get(p) != Elements::box) {
            box1 = p;
            break;
        }
    }
    Pos box2(-1, -1);
    for (auto p : v2.boxes()) {
        if (v1.room().get(p) != Elements::box) {
            box2 = p;
            break;
        }
    }
    assert(box1 != box2);
    Direction push = box1.to(box2);
    assert(push!=Direction::NotValid);
    Pos man_from = v1.man();
    Pos man_to = box1.move(reverse(push));

    MoveList mlst;
    if (man_from != man_to) {

        typedef Dijkstra<MatrixGraph> G;
        MatrixGraph g(v1.room());

        auto path = G::AStart_path(g, man_from, man_to);
        for (auto p : path.first) {
            auto d = man_from.to(p);
            mlst.check_push(d);
            man_from = p;
        }
    }

    mlst.check_push(add_push(push));
    man_from = box1;

    if (man_from != v2.man()) {
        typedef Dijkstra<MatrixGraph> G;
        MatrixGraph g(v2.room());

        auto path = G::AStart_path(g, man_from, v2.man());
        for (auto p : path.first) {
            auto d = man_from.to(p);
            mlst.check_push(d);
            man_from = p;
        }
    }
    assert(man_from == v2.man());
    return mlst;
}

