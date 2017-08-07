#ifndef BOARDGRAPH_H
#define BOARDGRAPH_H
#include "boardparam.h"
#include "board_api.h"

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

    // 这里需要特殊处理完成的状态，因为完成时人在哪里也不知道，所以特殊处理
    if (Board_API::is_done(p1) && Board_API::is_done(p2))
        return true;

    return p1.room == p2.room && RoomSlice(p1).can_man_to(p2.man_pos);
}


#endif // BOARDGRAPH_H
