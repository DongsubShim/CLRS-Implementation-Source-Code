#ifndef GRAPH_TRAVERSAL_HPP_
#define GRAPH_TRAVERSAL_HPP_
#include "graph_base.hpp"

class GraphTraversal : public GraphBase
{
    public:

        GraphTraversal(std::vector<std::vector<int>> edge_vector, bool is_directed) : GraphBase(edge_vector, is_directed) {
            InitGraphTraversal();
        }

        GraphTraversal() {
            InitGraphTraversal();
        }

        void PrintParent();

        // --- BFS ---
        void PrintBFSParent(int start);

        void FindPathBFS(int start, int end);

        void CC(); // print connected components via BFS 

        void TwoColor();

        // --- DFS ---
        void UndirCycles(int v);

        void ArticulationVertices(int v);

        void TopologicalSorting();

        void StrongComponents();


    protected:
        int *mapping;
        int *parent;
        bool *discovered;
        bool *processed;

        // --- BFS ---
        int *color;
        bool bipartite;
        std::queue<int> q;

        // --- DFS ---
        int* entry_time;
        int* exit_time;
        int current_time;
        bool finished;
        int* reachable_ancestor;
        int* tree_out_degree;
        enum edge_class {Tree, Back, Forward, Cross, Unclassified};
        std::stack<int> s;
        int* low;
        int* scc;
        int num_scc_found;
        

        // --- Protected Methods ---
        void InitGraphTraversal();

        static void DefaultPVE(int v, GraphTraversal* g) {};

        static void DefaultPVL(int v, GraphTraversal* g) {};

        static void DefaultPE(int v, int y, GraphTraversal* g) {};

        void UpdateMapping();

        void ResetParent(); 

        void ResetDiscoveredAndProcessed();

        // --- BFS ---
        void RecursivelyPrintPathBFS(int start, int end);

        void BFS(int start, void(*pve)(int, GraphTraversal*), void(*pvl)(int, GraphTraversal*), void(*pe)(int, int, GraphTraversal*));

        static void CCPVE(int v, GraphTraversal* g);   

        static void TwoColorPE(int v, int y, GraphTraversal* g);   

        static int ComplementColor(int x); 

        // --- DFS ---
        void ResetTime();

        void ResetForArticulationVertices();

        static void UndirCyclesPE(int x, int y, GraphTraversal* g);

        edge_class EdgeClassification(int x, int y);

        static void ArticulationVerticesPE(int x, int y, GraphTraversal* g);

        static void ArticulationVerticesPVE(int v, GraphTraversal* g);

        static void ArticulationVerticesPVL(int v, GraphTraversal* g);

        static void TopologicalSortingPE(int x, int y, GraphTraversal* g);

        static void TopologicalSortingPVL(int v, GraphTraversal* g);

        static void SCCPVE(int v, GraphTraversal* g);

        static void SCCPVL(int v, GraphTraversal* g);

        static void SCCPE(int x, int y, GraphTraversal* g);

        void PopComponent(int v);

        void DFS(int v, void(*pve)(int, GraphTraversal*), void(*pvl)(int, GraphTraversal*), void(*pe)(int, int, GraphTraversal*));
};

#include "graph_traversal_details.hpp"
#include "graph_bfs_details.hpp"
#include "graph_dfs_details.hpp"


#endif // GRAPH_TRAVERSAL_HPP_