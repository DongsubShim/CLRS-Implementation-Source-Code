#ifndef GRAPH_BASE_DETAILS_HPP_
#define GRAPH_BASE_DETAILS_HPP_
#include "graph_base.hpp" 

void GraphBase::PrintGraph() {
    std::cout << "\n------------ \n";
    std::cout << "Print Graph \n\n";

    if (directed) 
        std::cout << "Directed Graph \n";
    else
        std::cout << "Undirected Graph \n";
    

    std::cout << "Total Number of Vertices: " << num_vertices << "\n";
    std::cout << "Total Number of Edges: " << num_edges << "\n\n";

    int i;
    for (const int& i: vertices_set) {
        std::cout << "\n" << "Vertex Number: " << i << "\n";
        std::cout << "Degree: " << degree[i] << "\n";
        EdgeNode *p;
        p = edges[i];
        if (p != NULL) {
            std::cout << "| " << i << " |";
            while (p != NULL) {
                std::cout << " -- " << p -> y;
                p = p -> next;
            }
        }
        else
            std::cout << "No Edges!";

        std::cout << "\n";
    }
    std::cout << "\n ---------- \n";
}

void GraphBase::ResetGraph() {
    for (int i = 0; i <= MAXV; i++) {
        edges[i] = NULL;
        degree[i] = 0;
    }
}


void GraphBase::AddEdge(int x, int y, int w) {
    EdgeNode *temp;
    temp = new EdgeNode;
    temp -> y = y;
    temp -> weight = w;
    temp -> next = edges[x];
    edges[x] = temp;
    degree[x] ++;
    vertices_set.insert(x);
    vertices_set.insert(y);
}

GraphBase::GraphBase() {
    int i, m, x, y, w;

    ResetGraph();

    std::cout << "Please enter number of vertices and edges and directedness \n";
    std::cin >> num_vertices >> m >> directed;
    num_edges = 0;

    for (i = 1; i <= m; i++) {
        std::cout << "Edge Number: " << i << " out of " << m << " edges \n";
        std::cout << "Enter a vertex pair and a weight to form an edge \n";
        std::cin >> x >> y >> w;

        AddEdge(x, y, w);
        
        if (!directed) 
            AddEdge(y, x, w);

        num_edges ++;
    }
}


GraphBase::GraphBase(std::vector<std::vector<int>> edge_vector, bool is_directed) {
    int i, m, x, y, w;

    ResetGraph();

    directed = is_directed;
    m = edge_vector.size();

    for (int i = 0; i < m; i ++) {
        x = edge_vector[i][0];
        y = edge_vector[i][1];
        w = edge_vector[i][2];

        AddEdge(x, y, w);
        
        if (!directed) 
            AddEdge(y, x, w);

        num_edges ++;
    }
    num_vertices = vertices_set.size();    
}

#endif // GRAPH_TRAVERSAL_DETAILS_HPP_
