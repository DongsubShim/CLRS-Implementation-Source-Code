#ifndef GRAPH_DETAILS_HPP_
#define GRAPH_DETAILS_HPP_
#include "graph.hpp"

void Graph::ResetIntreeAndDistance() {
    for (int i = 0; i < num_vertices; i ++) {
        intree[i] = false;
        distance[i] = INT_MAX;
    }
}

void Graph::InitGraph() {
    intree = new bool[num_vertices];
    distance = new int[num_vertices];
    ResetIntreeAndDistance();
}

#endif // GRAPH_DETAILS_HPP_