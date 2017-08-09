#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "types.h"
#include "maskmatrix.h"

class MatrixGraph
{
    struct PosHash
    {
        size_t operator()(const Pos &p) const;
    };
public:
    typedef Pos vertex_t;
    typedef MaskMatrix::size_type distance_t;
    typedef PosHash hash_t;
    typedef std::vector<Pos> VertexVector;

    MatrixGraph(const ElementsMatrix &m);

    VertexVector neighbors(vertex_t v1) const;

    static distance_t heuristic(vertex_t v1, vertex_t v2)
    {
        return Manhattan_Distance(v1, v2);
    }

    static distance_t distance(vertex_t v1, vertex_t v2)
    {
        Q_UNUSED(v1);
        Q_UNUSED(v2);
        return 1;
    }

private:
    MaskMatrix matrix;
};

#endif // MATRIXGRAPH_H
