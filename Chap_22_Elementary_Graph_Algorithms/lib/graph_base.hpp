#ifndef GRAPH_BASE_HPP_
#define GRAPH_BASE_HPP_
#include "base.hpp"

#define MAXV 1000

typedef struct EdgeNode
{
    int weight;
    int y;
    EdgeNode *next;

} EdgeNode;

class GraphBase 
{
    public:
        GraphBase(std::vector<std::vector<int>> edge_vector, bool is_directed);

        GraphBase();

        void PrintGraph();

    protected:
        EdgeNode *edges[MAXV+1];
        int degree[MAXV+1];
        std::set<int> vertices_set;
        int num_edges;
        bool directed;
        int num_vertices;

        void BuildGraphInteractively();

        void ResetGraph();

        void AddEdge(int x, int y, int w);
};

#include "graph_base_details.hpp"

#endif // GRAPH_BASE_HPP_
