#ifndef GRAPH_DIJKSTRA_DETAILS_HPP_
#define GRAPH_DIJKSTRA_DETAILS_HPP_
#include "graph.hpp"

void Graph::PrintDijkstraPath(int i, int start) {
    if (i == start) {
        std::cout << "\nPath: " << start;
        return;
    } 
    int i_map = mapping[i];
    PrintDijkstraPath(parent[i_map], start);
    std::cout << " --> " << i;
    return;
}

void Graph::PrintDijkstraDistanceAndPath(int start) {
    int distance_to_i;
    std::cout << "\n\n---------------------------------" << std::endl;
    std::cout << "\nPrint Dijkstra Distance and Path" << std::endl;
    for (const int& i : vertices_set) {
        std::cout << "\n***From vertex " << start << " to vertex "<< i << "***" << std::endl;
        distance_to_i = distance[mapping[i]];
        
        if (distance_to_i < INT_MAX) {
            std::cout << "\nDistance: " << distance_to_i << std::endl;
            PrintDijkstraPath(i, start);
        }
        else {
            std::cout << "\nThere is no path from vertex " << start << " to vertex " << i;
        }
        std::cout << "\n" << std::endl;
    }
    std::cout << "\n\n---------------------------------" << std::endl;
}

void Graph::Dijkstra(int start) {
    /*O(n^2) where n is the number of vertices or nodes in the graph*/
    if (vertices_set.count(start) < 1) {
        std::cout << "\nVertex " << start << " is not present in the graph\n" << std::endl;
        return;
    }
    int v;
    int v_map;
    int w;
    int w_map;
    int weight;
    int new_distance;
    int i_map;
    int dist;
    EdgeNode *p;

    v = start;
    v_map = mapping[start];
    distance[v_map] = 0;

    while(intree[v_map] == false) {
        intree[v_map] = true;
        p = edges[v];
        while(p != NULL) {
            w = p -> y;
            w_map = mapping[w];
            weight = p -> weight;
            new_distance = distance[v_map] + weight;
            if (distance[w_map] > new_distance) {
                distance[w_map] = new_distance;
                parent[w_map] = v;
            }
            p = p -> next;
        }

        v = start;
        dist = INT_MAX;
        for (const int& i : vertices_set) {
            i_map = mapping[i];
            if (dist > distance[i_map] && intree[i_map] == false) {
                dist = distance[i_map];
                v = i;
            }
        }
        v_map = mapping[v];
    }
    PrintDijkstraDistanceAndPath(start);
    ResetParent();
    ResetIntreeAndDistance();
}

#endif // GRAPH_DIJKSTRA_DETAILS_HPP_