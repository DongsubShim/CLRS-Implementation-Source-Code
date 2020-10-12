#ifndef GRAPH_TRAVERSAL_DETAILS_HPP_
#define GRAPH_TRAVERSAL_DETAILS_HPP_
#include "graph_traversal.hpp"


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
    for (int i = 0; i < num_vertices; i++) {
        parent[i] = -1;
    }
}

void GraphTraversal::ResetDiscoveredAndProcessed() {
    for (int i = 0; i < num_vertices; i++) {
        discovered[i] = false;
        processed[i] = false;
    }
}

void GraphTraversal::InitGraphTraversal() {
    discovered = new bool[num_vertices];
    processed = new bool[num_vertices];
    parent = new int[num_vertices];
    mapping = new int[MAXV+1];
    UpdateMapping();
    ResetDiscoveredAndProcessed();
    ResetParent();
    // BFS
    color = new int[num_vertices];
    // DFS
    entry_time = new int[num_vertices];
    exit_time = new int[num_vertices];
    reachable_ancestor = new int[num_vertices];
    tree_out_degree = new int[num_vertices];
    current_time = 0;
    finished = false;
    low = new int[num_vertices];
    scc = new int[num_vertices];
    ResetTime();
    ResetForArticulationVertices();
}


#endif // GRAPH_TRAVERSAL_DETAILS_HPP_
