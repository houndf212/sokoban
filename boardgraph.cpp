#include "boardgraph.h"
#include <string>
#include "boxmover.h"
#include "board_api.h"
#include "assignmentproblem.h"

size_t BoardGraph::BoardHash::operator()(const BoardParam &param) const
{
    const ElementsMatrix &m = param.room;
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
    return BoxMover::next_move(param);
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
    assert(Board_API::is_done(v2));
    IntMatrix m;
    const auto size = v1.goals.size();
    m.resize(size, size);

    for (auto i=m.zero(); i<m.row_size(); ++i) {
        for (auto j=m.zero(); j<m.col_size(); ++j) {
            Pos box = v1.box_index[i];
            Pos goal = v1.goals[j];
            distance_t d = Manhattan_Distance(box, goal);
            m.set(Pos(i, j), d);
        }
    }

    auto p = AssignmentProblem::min_assignment<distance_t>(m);
    return p.second;
}

