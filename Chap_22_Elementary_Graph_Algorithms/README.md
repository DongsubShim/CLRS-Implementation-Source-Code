# Elementary Graph Algorithms
![](https://img.shields.io/badge/C++-blue.svg?style=flat&logo=c%2B%2B)


## Summary

- Adjacency List based Graph data strucuture

- Source code in lib directory


```sh
── Chap_22_Elementary_Graph_Algorithms
   ├── README.md
   ├── lib
   │   ├── base.hpp
   │   ├── graph_base.hpp
   │   ├── graph_base_details.hpp
   │   ├── graph_bfs_details.hpp
   │   ├── graph_dfs_details.hpp
   │   ├── graph_traversal.hpp
   │   └── graph_traversal_details.hpp
   ├── test_graph
   └── test_graph.cpp
```
## Example code in test_graph.cpp

```C++
int main()
{   // Create a graph object that supports graph traversal applications based on BFS and DFS
    GraphTraversal g; 

    /* 
    -- Example --
    Please enter number of vertices and edges and directedness 
    // <int number of vertices> <int number of edges> <0/1 for undirected/directed graph>
    >> 5 5 1 --> create a directed graph with 5 vertices and 5 edges 
    Edge Number: 1 out of 5 edges 
    Enter a vertex pair and a weight to form an edge 
    // <int vertex number> <int vertex number> <weight of edge>
    >> 1 0 1 --> edge (1, 0) with weight = 1
    
    and so on...
    */

    // Print edges
    g.PrintGraph();

    // Print parent of every vertex using BFS from vertex 2
    g.PrintBFSParent(2);

    // Find a path between vertex 2 and 4 using BFS
    g.FindPathBFS(2, 4);

    // Find a path between vertex 1 and 4 using BFS
    g.FindPathBFS(1, 4);

    // Return connected components using BFS
    g.CC();

    // Check if input graph is bipartite with BFS
    g.TwoColor();

    // Find out if there is an undirected cycle including vertex 1 using DFS
    g.UndirCycles(1);

    // Check if input graph is biconnected using DFS
    g.ArticulationVertices(1);

    // Run topological sorting with DFS - only for DAG
    g.TopologicalSorting();

    // Find strongly connected components using DFS - only for directed graphs
    g.StrongComponents();
    
}
```



## lib Directory Details

- base.hpp - header file for C++ libraries

- graph_base.hpp - base graph class declaration and member specification
                 - this class is in charge of creating graphs

- graph_base_details.hpp - base graph class constructor and member function definitions

- graph_traversal.hpp - graph traversal class declaration and member specification - inherits base graph class

- graph_traversal_details.hpp - graph traversal class constructor and common member function definitions

- graph_bfs_details.hpp - BFS related graph traversal class member function definitions

- graph_dfs_details.hpp - DFS related graph traversal class constructor and common member function definitions
