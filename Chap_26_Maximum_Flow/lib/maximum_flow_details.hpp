#ifndef MAXIMUM_FLOW_DETAILS_HPP_
#define MAXIMUM_FLOW_DETAILS_HPP_
#include "flow_graph.hpp"

void FlowGraph::AddZeroWeightEdges() {
    if (directed) {
        EdgeNode *e;
        int w;
        for (const int& i : vertices_set) {
            e = edges[i];
            while(e != NULL) {
                w = e -> y;
                if (!GetEdge(w, i))
                    AddEdge(w, i, 0);
                e = e -> next;
            }
        }
    } 
    else
        throw std::domain_error( "This implementation only accepts a directed graph that represents paths from source to sink" );
}

FlowGraph::FlowGraph(std::vector<std::vector<int>> edge_vector, bool is_directed) : Graph(edge_vector, is_directed) {
    AddZeroWeightEdges();
}


FlowGraph::FlowGraph() {
    AddZeroWeightEdges();
}

void FlowGraph::ResetResidualEdges() {
    EdgeNode *e;
    for (const int& i : vertices_set) {
        e = edges[i];
        while(e != NULL) {
            e -> flow = 0;
            e -> capacity = e -> weight;
            e -> residual = e -> capacity;
            e = e -> next;
        }
    }
}

bool FlowGraph::ValidEdge(EdgeNode *e) {
    if (e -> residual > 0) return true;
    return false;
}

void FlowGraph::BFS(int start, void(*pve)(int, FlowGraph*), void(*pvl)(int, FlowGraph*), void(*pe)(int, int, FlowGraph*)) {

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
            if (ValidEdge(p)) {
                y = p -> y;
                if (!processed[mapping[y]] || directed) 
                    pe(v, y, this);
                if (!discovered[mapping[y]]) {
                    q.push(y);
                    discovered[mapping[y]] = true;
                    parent[mapping[y]] = v;
                }
            }
            
            p = p -> next;
        }
        pvl(v, this);
        q.pop();
    }
}

EdgeNode* FlowGraph::GetEdge(int x, int y) {
    EdgeNode *e;
    e = edges[x];

    while(e != NULL) {
        if (y == e -> y)
            return e;
        e = e -> next;
    }
    return NULL;
}

int FlowGraph::GetAugmentingPathWeight(int start, int end) {
    EdgeNode *e;
    int ParentOfEnd = parent[mapping[end]];
    if (ParentOfEnd == -1) return 0;

    e = GetEdge(ParentOfEnd, end);

    if (start == ParentOfEnd)
        return e -> residual;
    return std::min(GetAugmentingPathWeight(start, ParentOfEnd), e -> residual);
}

void FlowGraph::AugmentPath(int start, int end, int AugmentingPathWeight) {
    if (start == end) return;

    EdgeNode *e;
    int ParentOfEnd = parent[mapping[end]];

    e = GetEdge(ParentOfEnd, end);

    e -> flow += AugmentingPathWeight;
    e -> residual -= AugmentingPathWeight;

    e = GetEdge(end, ParentOfEnd);
    e -> residual += AugmentingPathWeight;

    AugmentPath(start, ParentOfEnd, AugmentingPathWeight);
}

int FlowGraph::GetMaximumFlowFromSink(int sink) {
    EdgeNode *e;
    int maximum_flow = 0;

    e = edges[sink];
    while(e != NULL) {
        maximum_flow += e -> residual;
        e = e -> next;
    }
    return maximum_flow;
}

void FlowGraph::PrintResidual() {
    EdgeNode *e;
    int j;
    for (const int& i : vertices_set) {
        e = edges[i];
        while(e != NULL) {
            j = e -> y;
            std::cout << "Vertex " << i << " to Vertex " << j << " - Residual: " << e -> residual << std::endl;
            e = e -> next;
        }
    }
}

void FlowGraph::MaximumFlow(int source, int sink) {
    /*Use the Edmonds-Karp algorithm - O(n^3)*/ 

    int AugmentingPathWeight;

    ResetResidualEdges();

    BFS(source, DefaultFlowPVE, DefaultFlowPVL, DefaultFlowPE);

    AugmentingPathWeight = GetAugmentingPathWeight(source, sink);

    while(AugmentingPathWeight > 0) {

        AugmentPath(source, sink, AugmentingPathWeight);

        ResetParent();

        ResetDiscoveredAndProcessed();

        BFS(source, DefaultFlowPVE, DefaultFlowPVL, DefaultFlowPE);

        AugmentingPathWeight = GetAugmentingPathWeight(source, sink);
    }

    std::cout << "\n\nMaximum Flow is " << GetMaximumFlowFromSink(sink) << std::endl;
    PrintResidual();

    ResetParent();
}

#endif // MAXIMUM_FLOW_DETAILS_HPP_