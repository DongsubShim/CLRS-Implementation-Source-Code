#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include "graph_traversal.hpp"

class SetUnion 
{
    public:
        SetUnion() {};

        SetUnion(int num_elements) {
            p = new int[num_elements];
            size = new int[num_elements];
            num = num_elements;
            for (int i = 0; i < num_elements; i++) {
                p[i] = i;
                size[i] = 1;
            }
        }

        ~SetUnion() {
            delete[] p;
            delete[] size;
        }

        int Find(int x) {
            if (p[x] == x)
                return x;
            else 
                return Find(p[x]);
        }

        bool IsSamePartition(int x, int y) {
            return (Find(x) == Find(y));
        } 

        void Union(int x, int y) {
            int r_x, r_y;
            r_x = Find(x);
            r_y = Find(y);

            if (r_x == r_y) return;

            if (size[r_x] >= size[r_y]) {
                size[r_x] = size[r_x] + size[r_y];
                p[r_y] = r_x;
            }
            else {
                size[r_y] = size[r_x] + size[r_y];
                p[r_x] = r_y;
            }
        }
    
    private:
        int *p;
        int *size;
        int num;
};


typedef struct {
    // Auxiliary vertex struct for priority queue
    int v;
    int *v_distance;
} Vertex;


typedef struct {
    int v;
    int w;
    int weight;
} EdgePair;


class CompareVertex {

    public:
        bool operator()(Vertex x, Vertex y) {
            // if x has larger distance than y, x goes before y in priority queue
            return *(x.v_distance) > *(y.v_distance);
        }
};

class CompareEdge {

    public:
        bool operator()(EdgePair x, EdgePair y) {
            return x.weight > y.weight;
        }
};


class Graph : public GraphTraversal
{
    public:

        Graph(std::vector<std::vector<int>> edge_vector, bool is_directed) : GraphTraversal(edge_vector, is_directed) {
            InitGraph();
        }

        Graph() {
            InitGraph();
        }

        void PrimKnownEdges(int start);

        void Prim(int start);

        void Kruskal();

        void Dijkstra(int start);

    protected:
        bool *intree; // pointer to boolean array which indicates if each vertex belongs to MST
        int *distance; // pointer to integer array representing known smallest edge weight for each vertex

        void InitGraph();

        void ResetIntreeAndDistance();

        void PrintMST();

        void PrintDijkstraDistanceAndPath(int start);

        void PrintDijkstraPath(int i, int start);

        void UnionFind();

        bool IsUndirectedGraph();

        void EdgeToArray(std::priority_queue<EdgePair, std::vector<EdgePair>, CompareEdge> *q);

};

#include "graph_details.hpp"
#include "graph_mst_details.hpp"
#include "graph_dijkstra_details.hpp"

#endif // GRAPH_HPP_