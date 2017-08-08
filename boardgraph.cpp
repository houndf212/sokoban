#include "boardgraph.h"
#include <string>
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

static BoardGraph::distance_t fast_heuristic(const PosVector &v1, const PosVector &v2)
{

}
BoardGraph::distance_t BoardGraph::heuristic(const BoardGraph::vertex_t &v1, const BoardGraph::vertex_t &v2)
{
    //这个函数需要调整，当goal的数值过大的时候，这里的计算成为了瓶颈
    assert(v2.is_done());
    IntMatrix m;
    const auto size = v1.goals_size();
    m.resize(size, size);

    int index = 0;
    for (auto box : v1.boxes()) {
        for (auto goal : v1.goals()) {
            distance_t d = Manhattan_Distance(box, goal);
            Pos p(index/m.col_size(), index%m.col_size());
            m.set(p, d);
            index++;
        }
    }

    auto p = AssignmentProblem::min_assignment<distance_t>(m);
    return p.second;
}

