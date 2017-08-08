#include "boardgraph.h"
#include <string>
#include <queue>
#include "assignmentproblem.h"

size_t BoardGraph::BoardHash::operator()(const BoardParam &param) const
{
    const ElementsMatrix &m = param.room();
    std::string str;
    str.reserve(m.row_size()*m.col_size());

    for (int row=0; row<m.row_size(); ++row) {
        for (int col=0; col<m.col_size(); ++col) {
            Pos p(row, col);
            auto v = m.get(p);
            str.push_back(static_cast<char>(v));
        }
    }
    return std::hash<std::string>()(str);
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

    const auto size = v1.goals_size();
    if (size >= 4) {
        //退化为最短路径搜索
        return 0;
    }
    else {
        IntMatrix m;
        m.resize(size, size);

        int index = 0;
        for (auto box : v1.boxes()) {
            for (auto goal : v1.goals()) {
                distance_t d = Manhattan_Distance(box, goal);
                Pos p(index/size, index%size);
                m.set(p, d);
                index++;
            }
        }

        if (size <= 4) {
            auto p = AssignmentProblem::min_assignment<distance_t>(m);
            return p.second;
        }
        else
            return greedy_search(m);
    }

}

BoardGraph::distance_t BoardGraph::greedy_search(const IntMatrix &m)
{
    assert(m.row_size() == m.col_size());
    const auto size = m.row_size();
    BoolMatrix mask;
    mask.resize(size, size);
    mask.fill(false);

    auto is_mask = [&mask](Pos p) {
      return mask.get(p) == true;
    };

    auto mask_p = [&mask](Pos p) {
        for(auto i=mask.zero(); i<mask.row_size(); ++i) {
            mask.set(Pos(i, p.col()), true);
            mask.set(Pos(p.row(), i), true);
        }
    };

    auto comp = [&m](const Pos &p1, const Pos &p2) {
        return m.get(p1)>m.get(p2);
    };

    PosVector pq;

    for (auto row=m.zero(); row<m.row_size(); ++row) {
        for (auto col=m.zero(); col<m.col_size(); ++col) {
            pq.push_back(Pos(row, col));
            std::push_heap(begin(pq), end(pq), comp);
        }
    }

    distance_t weight = 0;
    auto n = 1;
    while(n!=size) {
        std::pop_heap(begin(pq), end(pq), comp);
        Pos min = pq.back();
        pq.pop_back();

        if (is_mask(min))
            continue;
        else {
            weight += m.get(min);
            mask_p(min);
            n++;
        }
    }
    return weight;
}

