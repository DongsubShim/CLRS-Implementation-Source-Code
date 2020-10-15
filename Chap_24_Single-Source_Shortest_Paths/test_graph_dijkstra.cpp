#include "graph.hpp"

int main() {
    bool is_directed = false;
    std::vector<std::vector<int>> edge_vector{{1, 2, 2}, {2, 3, 3}, {3, 4 ,3}, 
                                        {4, 5 ,5}, {5, 6, 4}, {6, 1, 3},
                                        {2, 6 ,5}, {2, 5, 4}, {3, 5, 2},
                                        {7, 9, 10}};

    Graph g(edge_vector, is_directed);
    g.Dijkstra(1);
    g.Dijkstra(3);
    g.Dijkstra(5);
    g.Dijkstra(7);
    g.Dijkstra(123);
}