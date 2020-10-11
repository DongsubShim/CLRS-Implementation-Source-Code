#ifndef GRAPH_DETAILS_HPP_
#define GRAPH_DETAILS_HPP_
#include "graph.hpp"

Graph::Graph() {
    intree = new bool[n];
    distance = new int[n];
    ResetIntreeAndDistance();
}

void Graph::ResetIntreeAndDistance() {
    for (int i = 0; i < n; i ++) {
        intree[i] = false;
        distance[i] = INT_MAX;
    }
}

#endif // GRAPH_DETAILS_HPP_