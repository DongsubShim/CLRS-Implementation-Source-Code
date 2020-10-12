#include "graph.hpp"

int main() {
    Graph g;
    g.PrimKnownEdges(1);
    g.Prim(1);
    g.Kruskal();
}