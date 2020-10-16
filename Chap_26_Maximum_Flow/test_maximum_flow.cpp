#include "flow_graph.hpp"

int main() {
    bool is_directed = true;
    // source: 1, sink: 4
    // Use directed graph to represent all paths from source to sink
    std::vector<std::vector<int>> edge_vector{{1, 2, 10}, {2, 3, 5}, {3, 4 ,7}, 
                                        {1, 6 ,8}, {6, 5, 10}, {5, 4, 10},
                                        {2, 6 ,2}, {5, 3, 8}};

    FlowGraph g(edge_vector, is_directed);

    g.MaximumFlow(1, 4);

}