#ifndef GRAPH_TRAVERSAL_DETAILS_HPP_
#define GRAPH_TRAVERSAL_DETAILS_HPP_
#include "graph_traversal.hpp"

GraphTraversal::GraphTraversal() {
    discovered = new bool[n];
    processed = new bool[n];
    parent = new int[n];
    mapping = new int[MAXV+1];
    UpdateMapping();
    ResetDiscoveredAndProcessed();
    ResetParent();
    // BFS
    color = new int[n];
    // DFS
    entry_time = new int[n];
    exit_time = new int[n];
    reachable_ancestor = new int[n];
    tree_out_degree = new int[n];
    current_time = 0;
    finished = false;
    low = new int[n];
    scc = new int[n];
    ResetTime();
    ResetForArticulationVertices();
}

void GraphTraversal::PrintParent() {
    std::cout << "\n--------------------------- \n";
    std::cout << "Print Parent" << "\n\n";

    for (const int& i : vertices_set) {
        std::cout << "Parent of " << i << " is " << parent[mapping[i]] << "\n";
    }

    std::cout << "\n--------------------------- \n";
}

void GraphTraversal::UpdateMapping() {
    int j = 0;
    for (const int& i : vertices_set) {
        mapping[i] = j;
        j++;
    }
}

void GraphTraversal::ResetParent() {
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
}

void GraphTraversal::ResetDiscoveredAndProcessed() {
    for (int i = 0; i < n; i++) {
        discovered[i] = false;
        processed[i] = false;
    }
}

#endif // GRAPH_TRAVERSAL_DETAILS_HPP_
