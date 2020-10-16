#ifndef FLOW_GRAPH_HPP_
#define FLOW_GRAPH_HPP_
#include "graph.hpp"

class FlowGraph : public Graph 
{
    public:
        FlowGraph(std::vector<std::vector<int>> edge_vector, bool is_directed);

        FlowGraph();

        void MaximumFlow(int source, int sink);

    protected:
        void AddZeroWeightEdges();

        void BFS(int start, void(*pve)(int, FlowGraph*), void(*pvl)(int, FlowGraph*), void(*pe)(int, int, FlowGraph*));

        bool ValidEdge(EdgeNode *e);

        EdgeNode* GetEdge(int x, int y);

        void AugmentPath(int start, int end, int AugmentingPathWeight);

        int GetAugmentingPathWeight(int start, int end);

        void ResetResidualEdges();

        int GetMaximumFlowFromSink(int sink);

        static void DefaultFlowPVE(int v, FlowGraph* g) {};

        static void DefaultFlowPVL(int v, FlowGraph* g) {};

        static void DefaultFlowPE(int v, int y, FlowGraph* g) {};

        void PrintResidual();


};

#include "maximum_flow_details.hpp"

#endif // FLOW_GRAPH_HPP_