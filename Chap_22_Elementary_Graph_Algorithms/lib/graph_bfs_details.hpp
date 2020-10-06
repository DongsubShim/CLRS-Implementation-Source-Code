#ifndef GRAPH_BFS_DETAILS_HPP_
#define GRAPH_BFS_DETAILS_HPP_
#include "graph_traversal.hpp" 

void GraphTraversal::PrintBFSParent(int start) {
    std::cout << "\n--------------------------- \n";
    std::cout << "Print BFS Parent - start at: " << start << "\n\n";
    int j, p;

    BFS(start, DefaultPVE, DefaultPVL, DefaultPE);

    for (const int& i : vertices_set) {
        j = mapping[i];
        p = parent[j];
        std::cout << "Parent of " << i << " is " << p << "\n";
    }

    std::cout << "\n--------------------------- \n";
    ResetDiscoveredAndProcessed();
    ResetParent();
}

void GraphTraversal::FindPathBFS(int start, int end) {
    BFS(start, DefaultPVE, DefaultPVL, DefaultPE);
    std::cout << "\n\nFind Path using BFS \n\n";
    RecursivelyPrintPathBFS(start, end);
    std::cout << " | End \n\n" ;
    ResetDiscoveredAndProcessed();
    ResetParent();
}

void GraphTraversal::RecursivelyPrintPathBFS(int start, int end) {
    if (start == end || end == -1)
        std::cout << "START: " << start ;
    else 
    {
        RecursivelyPrintPathBFS(start, parent[mapping[end]]);
        std::cout << " --> " << end;
    }
}

void GraphTraversal::BFS(int start, void(*pve)(int, GraphTraversal*), void(*pvl)(int, GraphTraversal*), void(*pe)(int, int, GraphTraversal*)) {

    int v, y;
    EdgeNode *p;

    discovered[mapping[start]] = true;
    q.push(start);

    while(!q.empty()) {
        v = q.front();
        processed[mapping[v]] = true;
        pve(v, this);
        p = edges[v];
        
        while(p != NULL) {
            y = p -> y;
            if (!processed[mapping[y]] || directed) 
                pe(v, y, this);
            if (!discovered[mapping[y]]) {
                q.push(y);
                discovered[mapping[y]] = true;
                parent[mapping[y]] = v;
            }
            p = p -> next;
        }
        pvl(v, this);
        q.pop();
    }
}

void GraphTraversal::CCPVE(int v, GraphTraversal* g) {
    std::cout << " - " << v;
}

void GraphTraversal::CC() {
    
    int c = 0;
    int i;
    for (const int& v : vertices_set) {
        if (!discovered[mapping[v]]) {
            c += 1;
            std::cout << "\n\nComponent: | " << c << " | ";
            BFS(v, CCPVE, DefaultPVL, DefaultPE);
        }
    }
    std::cout << std::endl;
    ResetDiscoveredAndProcessed();
    ResetParent();
}

int GraphTraversal::ComplementColor(int x) {
    if (x == 1)
        return 0;
    if (x == 0)
        return 1;
    return -1;
}

void GraphTraversal::TwoColorPE(int v, int y, GraphTraversal* g) {
    if (g -> color[g -> mapping[v]] == g -> color[g -> mapping[y]]) {
        std::cout << "Not bipartite due to edge ( " << v << " , " << y << " )" << std::endl;
        g -> bipartite = false;
        return;
    }

    g -> color[g -> mapping[y]] = ComplementColor(g -> color[g -> mapping[v]]);
}

void GraphTraversal::TwoColor() {
    
    for (const int& v : vertices_set) {
        color[mapping[v]] = -1;
    }

    bipartite = true;

    for (const int& v : vertices_set) {
        if (!discovered[mapping[v]])
            color[mapping[v]] = 1;
            BFS(v, DefaultPVE, DefaultPVL, TwoColorPE);
    }
    std::cout << "Bipartite: " << bipartite << std::endl;
    ResetDiscoveredAndProcessed();
    ResetParent();
}

#endif // GRAPH_BFS_DETAILS_HPP_
