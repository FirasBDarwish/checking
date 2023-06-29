/*

Difference between .resize() and .assign for vectors: https://stackoverflow.com/questions/19673311/stl-vector-resize-and-assign

THE LOOPING MECHANISM IN THE MAIN ALLOWS FOR IT TO COVER COMPONENTS THAT ARE NOT CONNECTED (if there are more
than one island). it also allows the base node to start at 0.

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

            //add the second line if you want it to be undirected
            //adjList[edge.dest].push_back(edge.src); 
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
        {1, 2}, {0, 2}, {2, 0}, {0, 1}, {2, 3}, {3, 3}
    };

    //prints first src node of first edge (1)
    //cout << edges[0].src << endl;

    // total number of nodes in the graph (labelled from 0 to 12)
    int n = 4;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n, false);
 
    // Perform DFS traversal from all undiscovered nodes to
    // cover all connected components of a graph
        //also works but starts with 0 as base node, and covers components that are not connected.
    for (int i = 0; i < n; i++)
    {
        if (discovered[i] == false) {
            DFS(graph, i, discovered);
        }
    }

    //how i would approach it: with a source node. but that only gives you connected components
    //in that island. There may be other islands that are separate that won't be produced unless you use
    //the above for loop
    //DFS(graph, 2, discovered);
 
    return 0;
}