#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include "graph_traversal.hpp"


class Graph : public GraphTraversal
{
    public:
        Graph();
        void PrimKnownEdges(int start);

    protected:
        bool *intree; // pointer to boolean array which indicates if each vertex belongs to MST
        int *distance; // pointer to integer array representing known smallest edge weight for each vertex

        void ResetIntreeAndDistance();

        void PrintMST();

};

#include "graph_details.hpp"
#include "graph_mst_details.hpp"

#endif // GRAPH_HPP_