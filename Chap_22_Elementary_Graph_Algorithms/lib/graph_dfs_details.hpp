#ifndef GRAPH_DFS_DETAILS_HPP_
#define GRAPH_DFS_DETAILS_HPP_
#include "graph_traversal.hpp"

void GraphTraversal::ResetTime() {
    for (int i = 0; i < num_vertices; i++) {
        entry_time[i] = 0;
        exit_time[i] = 0;
    }
}

void GraphTraversal::ResetForArticulationVertices() {
    for (int i = 0; i < num_vertices; i++) {
        reachable_ancestor[i] = 0;
        tree_out_degree[i] = 0;
    }
}

void GraphTraversal::ArticulationVerticesPVE(int v, GraphTraversal* g) {
    g -> reachable_ancestor[g -> mapping[v]] = v;
}

void GraphTraversal::ArticulationVerticesPVL(int v, GraphTraversal* g) {
    bool is_parent_of_v_root;
    int time_v;
    int time_parent_v;

    int v_mapping = g -> mapping[v];
    int parent_v = g -> parent[v_mapping];

    // check if v is the root of the DFS tree
    // if so, v could be a root cutnode
    if (parent_v < 1) {
        // if v has more than 1 connection
        // v is a root cutnode
        if(g -> tree_out_degree[v_mapping] > 1)
            std::cout << "\n\nRoot articulation vertex: " << v << "\n" << std::endl;
        // if just 1 connection or none, v cannot be an articulation vertex
        return;
    }

    int v_rechable_ancestor = g -> reachable_ancestor[v_mapping];
    int parent_v_mapping = g -> mapping[parent_v];
    int parent_v_rechable_ancestor = g -> reachable_ancestor[parent_v_mapping];

    // v is not the root of the DFS tree
    // check if v's parent is the root
    is_parent_of_v_root = (g -> parent[parent_v_mapping] < 1);

    // if v's parent is not the root
    if (!is_parent_of_v_root) {
        // if v's reachable anscestor is its parent, its parent is a parent cutnode
        if (v_rechable_ancestor == parent_v)
            std::cout << "\n\nParent articulation vertex: " << parent_v << "\n" << std::endl;

        // if v's reachable anscestor is itself, its parent is a bridge cutnode
        if (v_rechable_ancestor == v) {
            std::cout << "\n\nBridge articulation vertex: " << parent_v << "\n" << std::endl;

            // -- if v is not a leaf, it is also a bridge cutnode
            if (g -> tree_out_degree[v_mapping] > 0)
                std::cout << "\n\nBridge articulation vertex: " << v << "\n" << std::endl;
        }
    }

    time_v = g -> entry_time[g -> mapping[v_rechable_ancestor]];
    time_parent_v = g -> entry_time[g -> mapping[parent_v_rechable_ancestor]];

    // update v's parent's rechable ancestor if applicable
    if (time_v < time_parent_v)
        g -> reachable_ancestor[parent_v_mapping] = v_rechable_ancestor;
}

void GraphTraversal::ArticulationVerticesPE(int x, int y, GraphTraversal* g) {
    bool is_back_edge = (g -> EdgeClassification(x, y) == Back);
    if (is_back_edge) {
        // back edge: y could be x's earliest reachable ancestor
        // map vertex number to index in arrays of length n
        int x_mapping = g -> mapping[x];
        int y_mapping = g -> mapping[y];
        int x_rechable_ancestor = g -> reachable_ancestor[x_mapping];
        int x_rechable_ancestor_mapping = g -> mapping[x_rechable_ancestor];
        if (g -> entry_time[y_mapping] < g -> entry_time[x_rechable_ancestor_mapping]) {
            // y has been discovered earlier than x's earliest reachable ancestor
            // therefore, y becomes x's earliest reachable ancestor
            g -> reachable_ancestor[x_mapping] = y;
        }
    }
    else
        g -> tree_out_degree[g -> mapping[x]] += 1;
}

void GraphTraversal::ArticulationVertices(int v) {
    DFS(v, ArticulationVerticesPVE, ArticulationVerticesPVL, ArticulationVerticesPE);
    ResetDiscoveredAndProcessed();
    ResetForArticulationVertices();
    ResetParent();
    ResetTime();
}

GraphTraversal::edge_class GraphTraversal::EdgeClassification(int x, int y) {
    // for edge (x, y)
    int x_mapping = mapping[x];
    int y_mapping = mapping[y];
    // this is a tree edge if x is y's parent
    if (parent[y_mapping] == x)
        return Tree;
    /* 
    this is a back edge if y has been discovered but not yet processed, 
    implicit condition for an undirected back edge: parent[y_mapping] != x
    if false, the undirected edge has been visited twice! (e.g., x -> y then y -> x)
    tree edge condition above already covers this case so no confusion for undirected edges
    */
    if (discovered[y_mapping] && !processed[y_mapping])
        return Back;
    // this is a forward edge if y has been processed and y is entered later than x
    if (processed[y_mapping] && entry_time[y_mapping] > entry_time[x_mapping])
        return Forward;
    // this is a cross edge if y has been processed and y is entered earlier than x
    if (processed[y_mapping] && entry_time[y_mapping] < entry_time[x_mapping])
        return Cross;
    
    return Unclassified;
}

void GraphTraversal::UndirCyclesPE(int x, int y, GraphTraversal* g) {
    if (g -> EdgeClassification(x, y) == Back) {
        std::cout << "\nCycle found between " << y << " and " << x  << std::endl; 
        g -> RecursivelyPrintPathBFS(y, x);
        std::cout << std::endl;
        g -> finished = true;
    }
}

void GraphTraversal::UndirCycles(int v) {
    DFS(v, DefaultPVE, DefaultPVL, UndirCyclesPE);
    ResetDiscoveredAndProcessed();
    ResetParent();
    ResetTime();
    finished = false;
}

void GraphTraversal::TopologicalSortingPE(int x, int y, GraphTraversal* g) {
    int edge_class = g -> EdgeClassification(x, y);
    if (edge_class == Back) 
        std::cout << "\n\nDirected cycle found - this is not a DAG\n" << std::endl;
}


void GraphTraversal::TopologicalSortingPVL(int v, GraphTraversal* g ) {
    g -> s.push(v);
}

void GraphTraversal::TopologicalSorting() {
    for (const int& i : vertices_set) {
        if (!discovered[mapping[i]])
            DFS(i, DefaultPVE, TopologicalSortingPVL, TopologicalSortingPE);
    }

    std::cout << "\n\nTopological Sorting" << std::endl;
    std::cout << "Start --> ";
    while(!s.empty()) {
        std::cout << s.top() << " --> ";
        s.pop();
    }
    std::cout << "End \n" << std::endl;

    ResetDiscoveredAndProcessed();
    ResetParent();
    ResetTime();
}

void GraphTraversal::PopComponent(int v) {
    int t;
    num_scc_found += 1;

    do {
        t = s.top();
        s.pop();
        scc[mapping[t]] = num_scc_found;
    }
    while (t != v);
}

void GraphTraversal::SCCPVE(int v, GraphTraversal* g) {
    g -> s.push(v);
}

void GraphTraversal::SCCPVL(int v, GraphTraversal* g) {
    int v_mapping = g -> mapping[v];
    int low_v = g -> low[v_mapping];
    int low_v_mapping = g -> mapping[low_v];
    int low_v_entry_time = g -> entry_time[low_v_mapping];

    int v_parent = g -> parent[v_mapping];
    int v_parent_mapping = g -> mapping[v_parent];
    int low_v_parent = g -> low[v_parent_mapping];
    int low_v_parent_mapping = g -> mapping[low_v_parent];
    int low_v_parent_mapping_entry_time = g -> entry_time[low_v_parent_mapping];

    if (low_v == v) {
        g -> PopComponent(v);
    }

    if (v_parent > 0) {
        if (low_v_entry_time < low_v_parent_mapping_entry_time)
            g -> low[v_parent_mapping] = low_v;
    }
}

void GraphTraversal::SCCPE(int x, int y, GraphTraversal* g) {
    int edge_class = g -> EdgeClassification(x, y);
    int x_mapping = g -> mapping[x];
    int y_mapping = g -> mapping[y];
    int low_x = g -> low[x_mapping];
    int low_x_mapping = g -> mapping[low_x];
    int low_x_entry_time = g -> entry_time[low_x_mapping];
    int y_entry_time = g -> entry_time[y_mapping];

    if (edge_class == Back) {
        // if y is discovered earlier than the oldest vertex in the component
        // set y as the oldest vertex in the component
        if (y_entry_time < low_x_entry_time)
            g -> low[x_mapping] = y;
    }

    if (edge_class == Cross) {
        if (g -> scc[y_mapping] == -1) {
            if (y_entry_time < low_x_entry_time)
                g -> low[x_mapping] = y;
        }
    }
}

void GraphTraversal::StrongComponents() {
    int i;
    num_scc_found = 0;

    for (const int& v : vertices_set) {
        low[mapping[v]] = v;
        scc[mapping[v]] = -1;
    }

    for (const int& v: vertices_set) {
        if (!discovered[mapping[v]])
            DFS(v, SCCPVE, SCCPVL, SCCPE);
    }

    std::cout << "\n\nPrint SCC" << std::endl;
    for (const int& v : vertices_set) {
        std::cout << v << " in SCC " << scc[mapping[v]] << std::endl;
    }

    ResetDiscoveredAndProcessed();
    ResetParent();
    ResetTime();

}

void GraphTraversal::DFS(int v, void(*pve)(int, GraphTraversal*), void(*pvl)(int, GraphTraversal*), void(*pe)(int, int, GraphTraversal*)) {
    EdgeNode *p;
    int y;

    if (finished) return;

    discovered[mapping[v]] = true;
    current_time += 1;
    entry_time[mapping[v]] = current_time;
    pve(v, this);
    p = edges[v];
    while(p != NULL) {
        y = p -> y;
        if (!discovered[mapping[y]]) {
            parent[mapping[y]] = v;
            pe(v, y, this);
            DFS(y, pve, pvl, pe);
        }
            
        else if (!processed[mapping[y]] && parent[mapping[v]] != y || directed)
            pe(v, y, this);
            
        if (finished) return;
        p = p -> next;
    }

    pvl(v, this);
    current_time += 1;
    exit_time[mapping[v]] = current_time;
    processed[mapping[v]] = true;
}

#endif // GRAPH_DFS_DETAILS_HPP_
