#ifndef BOARDGRAPH_H
#define BOARDGRAPH_H
#include "boardparam.h"

class BoardGraph
{
    struct BoardHash
    {
        size_t operator()(const BoardParam &param) const;
    };
public:
    typedef BoardParam vertex_t;
    typedef type_size distance_t;
    typedef BoardHash hash_t;

    typedef std::vector<vertex_t> VertexVector;
    typedef std::list<vertex_t> VertexList;

    static VertexList neighbors(const vertex_t& param);
    static distance_t distance(const vertex_t &v1, const vertex_t &v2);
    static distance_t heuristic(const vertex_t &v1, const vertex_t &v2);
};

#include "roomslice.h"
inline bool operator == (const BoardParam &p1, const BoardParam &p2)
{
    assert(p1.goals == p2.goals);
    bool b = p1.man_pos == p2.man_pos && p1.room == p2.room;
    if (b) {
        assert(RoomSlice(p1).can_man_to(p2.man_pos));
    }
    return b;
}


#endif // BOARDGRAPH_H
