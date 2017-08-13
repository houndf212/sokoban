#include "matrixgraph.h"
#include "dijkstra.h"

size_t MatrixGraph::PosHash::operator()(const Pos &p) const
{
    constexpr int half = sizeof(p.row())*8/2;
    static_assert(sizeof(p.row())<=sizeof(size_t)/2, "");
    size_t c = static_cast<size_t>(p.row()) << half | static_cast<size_t>(p.col());
    return std::hash<size_t>()(c);
}

MatrixGraph::MatrixGraph(const ElementsMatrix &m)
{
    matrix.resize(m.row_size(), m.col_size());
    matrix.unmask_all();

    for (auto row=m.szero(); row<m.row_size(); ++row) {
        for (auto col=m.szero(); col<m.col_size(); ++col) {
            Pos p(row, col);
            auto e = m.get(p);
            //mask表示可行路径
            if (e == Elements::floor)
                matrix.mask(p);
        }
    }
}

PosList MatrixGraph::shortest_path(Pos start, Pos goal) const
{
    typedef Dijkstra<MatrixGraph> G;
    auto path = G::AStart_path(*this, start, goal);
    return path.first;
}

MatrixGraph::VertexVector MatrixGraph::neighbors(MatrixGraph::vertex_t v1) const
{
    VertexVector vec;
    auto func = [&] (Pos p) {
        if (matrix.isInMatrix(p) && matrix.is_mask(p))
            vec.push_back(p);
    };
    func(Pos(v1.row()+1, v1.col()));
    func(Pos(v1.row()-1, v1.col()));
    func(Pos(v1.row(), v1.col()+1));
    func(Pos(v1.row(), v1.col()-1));
    return vec;
}
