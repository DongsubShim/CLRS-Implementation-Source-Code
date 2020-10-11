#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include "graph_traversal.hpp"

typedef struct {
    // Auxiliary vertex struct for priority queue
    int v;
    int *v_distance;
} Vertex;


class CompareVertex {

    public:
        bool operator()(Vertex x, Vertex y) {
            // if x has larger distance than y, x goes before y in priority queue
            return *(x.v_distance) > *(y.v_distance);
        }
};


class Graph : public GraphTraversal
{
    public:
        Graph();

        void PrimKnownEdges(int start);

        void Prim(int start);

        void Kruskal();

    protected:
        bool *intree; // pointer to boolean array which indicates if each vertex belongs to MST
        int *distance; // pointer to integer array representing known smallest edge weight for each vertex

        void ResetIntreeAndDistance();

        void PrintMST();

        void UnionFind();

        bool IsUndirectedGraph();

};

#include "graph_details.hpp"
#include "graph_mst_details.hpp"

#endif // GRAPH_HPP_