/*

Difference between .resize() and .assign for vectors: https://stackoverflow.com/questions/19673311/stl-vector-resize-and-assign

*/

#include <iostream>
#include <vector>
using namespace std;
 
// Data structure to store a graph edge
struct Edge {
    int src, dest;

    Edge(int a, int b)
    {
        this->src = a;
        this->dest = b;
    }
};

class Graph
{
    public:
    vector<vector<int>> adjList;

    Graph(vector<Edge> &edges, int n)
    {
        adjList.resize(n);

        for(auto edge: edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src); 
        }
        return;
    }

};

void DFS(Graph &graph, int v, vector<bool> &discovered)
    {
        cout << v << " ";
        discovered[v] = true;
        for(auto adj: graph.adjList[v])
        {
            if(discovered[adj] != true)
            {
                discovered[adj] = true;
                DFS(graph, adj, discovered);
            }
        }
        return;
    }

int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        // Notice that node 0 is unconnected
        {1, 2}, {1, 7}, {1, 8}, {2, 3}, {2, 6}, {3, 4},
        {3, 5}, {8, 9}, {8, 12}, {9, 10}, {9, 11}
    };

    //prints first src node of first edge (1)
    //cout << edges[0].src << endl;

    // total number of nodes in the graph (labelled from 0 to 12)
    int n = 13;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);
 
    // Perform DFS traversal from all undiscovered nodes to
    // cover all connected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (discovered[i] == false) {
            DFS(graph, i, discovered);
        }
    }
 
    return 0;
}