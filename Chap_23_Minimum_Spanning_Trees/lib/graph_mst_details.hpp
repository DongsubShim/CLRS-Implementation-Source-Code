#ifndef GRAPH_MST_DETAILS_HPP_
#define GRAPH_MST_DETAILS_HPP_
#include "graph.hpp"

void Graph::PrintMST() {
    std::cout << "\n--------------------------- \n";
    std::cout << "Print MST" << "\n\n";

    for (const int& i : vertices_set) {
        std::cout << "Parent of " << i << " is " << parent[mapping[i]] << "\n";
    }

    std::cout << "\n--------------------------- \n";
}

void Graph::PrimKnownEdges(int start) {
    /* Run Prim's algorithm - this version considers cheapest known edges only - it avoids examining all edges at each iteration
    O(n^2) where n is the number of vertices in the graph */
    if (directed == 1) {
        std::cout << "\n\nPrim's Algorithm works only for weighted undirected graphs.\nIt is not applicable for the input directed graph.\n" << std::endl;
        return;
    }
    int i; // counter
    EdgeNode *p; // temporary pointer to an edge node
    int v; // vertex whose edges are examined for distance update based on edge weight: weight(v, w)
    int w; // one of the vertices adjacent to v - weight of edge (v, w) is examined for distance update
    int w_map; // mapping of vertex w for array indexing
    int weight; // edge weight for (v, w)
    int dist; // smallest edge weight among all vertices not in MST
    int j_map; // mapping of vertex j for array indexing
    int j_distance; // known smallest edge weight involving vertex j

    distance[mapping[start]] = 0; // distance from start to start is trivially zero - assuming no self-loop 
    v = start; // begin with examing edges of start

    while(intree[mapping[v]] == false) {
        intree[mapping[v]] = true; // include vertex v in MST - v has the smallest edge weight among those not in MST
        p = edges[v]; // pointer to v's edges
        while(p != NULL) {
            w = p -> y; // get end-point of an edge pointed by p
            weight = p -> weight; // get edge weight
            w_map = mapping[w]; // get w's array index
            // if the smallest edge weight for w seen so far is larger than the current edge weight
            // and w is not in MST, update w's smallest edge weight
            // w must not be in MST - without this condition, MST path flips e.g., parent of v becomes w later on
            if ((distance[w_map] > weight) && (intree[w_map] == false)) {
                distance[w_map] = weight;
                parent[w_map] = v; // update parent for MST structure - parent of w will be updated over iterations until it's in MST
            }
            p = p -> next; // get next edge of v
        }

        v = start; // reset v
        dist = INT_MAX;
        for (const int& j : vertices_set) {
            j_map = mapping[j];
            j_distance = distance[j_map];
            // if vertex j is not in MST and it has the smallest edge weight among those not in MST
            // examine j in the next iteration - i.e., j is going to be included in MST
            if((intree[j_map] == false) && dist > j_distance) {
                dist = j_distance;
                v = j;
            }
        }
    }
    PrintMST();
    ResetParent();
    ResetIntreeAndDistance();
}

#endif // GRAPH_MST_DETAILS_HPP_

