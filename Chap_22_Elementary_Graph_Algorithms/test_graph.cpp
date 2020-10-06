#include "lib/graph_traversal.hpp"

int main()
{   
    GraphTraversal g;
    g.PrintGraph();
    g.PrintBFSParent(2);
    g.FindPathBFS(2, 4);
    g.FindPathBFS(1, 4);
    g.CC();
    g.TwoColor();
    g.UndirCycles(1);
    g.ArticulationVertices(1);
    g.TopologicalSorting();
    g.StrongComponents();
    
}