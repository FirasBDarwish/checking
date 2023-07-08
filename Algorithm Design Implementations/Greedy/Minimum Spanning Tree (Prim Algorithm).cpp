/*

This is based on section 5.5 of Algorithm Design.

We seek to use a priority queue here to improve the time complexity.

*/

// STL implementation of Prim's algorithm for MST
#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
 
// iPair ==>  Integer Pair
typedef pair<int, int> iPair;
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
 
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list< pair<int, int> > *adj;

public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
 
    // Print MST using Prim's algorithm
    void primMST(int src);
};

Graph::Graph(int V)
{
    this->V = V;
    this->adj = new list<pair<int,int>>[V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v,w));
    adj[v].push_back(make_pair(u,w));
}

void Graph::primMST(int src)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > min_heap;

    //equivalent to dist in our last example
    vector<int> key(V,INF);

    //parent[v] = u says that node v was brought into the MST by being connected to node u
    vector<int> parent(V,-1);

    vector<bool> in_MST(V,false);

    min_heap.push(make_pair(0,src));
    key[src] = 0;

    while(!min_heap.empty())
    {

        int u = min_heap.top().second;
        min_heap.pop();

        if(in_MST[u] == true)
            continue;

        in_MST[u] = true;

        for(auto adjacent: adj[u])
        {
            int v = adjacent.first;
            int weight = adjacent.second;

            if(in_MST[v] == false && weight < key[v])
            {
                key[v] = weight;
                min_heap.push(make_pair(weight, v));
                parent[v] = u;
            }
        }

    }

    // Print edges of MST using parent array
    for (int i = 1; i < V; i++) //as source does not have a parent
        printf("%d - %d\n", parent[i], i);

}

// Driver program to test methods of graph class
int main()
{
    // create the graph given in above figure
    int V = 9;
    Graph g(V);
 
    //  making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
 
    g.primMST(0);
 
    return 0;
}

