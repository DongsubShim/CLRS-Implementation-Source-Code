# Minimum Spanning Trees
![](https://img.shields.io/badge/C++-blue.svg?style=flat&logo=c%2B%2B)


## Summary

- Adjacency List based Graph data strucuture

- Source code in lib directory


```sh
── Chap_23_Minimum_Spanning_Trees
   ├── README.md
   ├── lib
   │   ├── graph.hpp
   │   ├── graph_details.hpp
   │   └── graph_mst_details.hpp
   └── test_graph_weighted.cpp
```
## Example code in test_graph_weighted.cpp

```C++
int main() {
    Graph g;
    g.PrimKnownEdges(1);
}
```

## Compiling with g++
- Replace \<path\> with path to CLRS-Implementation-Source-Code/
```bash
g++ -g <path>/CLRS-Implementation-Source-Code/Chap_23_Minimum_Spanning_Trees/test_graph_weighted.cpp -o <path>/CLRS-Implementation-Source-Code/Chap_23_Minimum_Spanning_Trees/test_graph_weighted -I <path>/CLRS-Implementation-Source-Code/Chap_23_Minimum_Spanning_Trees/lib -I <path>/CLRS-Implementation-Source-Code/Chap_22_Elementary_Graph_Algorithms/lib
```
