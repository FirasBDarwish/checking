/*

This is based on section 5.5 of Algorithm Design.

Using: https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/

We seek to use a priority queue here to improve the time complexity.

greater<pair<int,int>> is actually a struct: https://stackoverflow.com/questions/71429544/what-does-greaterpairint-int-do-actually

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

    //sort of like dist in our last example, but not distance from node, just the smallest weight connected to that node
        //so key[v] is the smallest weight of an edge connected to key[v]
    vector<int> key(V,INF);

    //parent[v] = u says that node v was brought into the MST by being connected to node u
    vector<int> parent(V,-1);

    //like the vector<bool> visited, which is commonly used in Djikstra to note visited nodes.
    vector<bool> in_MST(V,false);

    min_heap.push(make_pair(0,src));
    key[src] = 0;

    int i = 0;

    while(!min_heap.empty())
    {

        int u = min_heap.top().second;
        min_heap.pop();

        //Different key values for same vertex may exist in the priority queue.
          //The one with the least key value is always processed first.
          //Therefore, ignore the rest.
        if(in_MST[u] == true)
            continue;

        in_MST[u] = true; //officially visited as it is the item in min_heap with smallest key (smallest weight)

        for(auto adjacent: adj[u])
        {
            int v = adjacent.first;
            int weight = adjacent.second;

            //this is important because we already visited in_MST[v] no point in adding.
            if(in_MST[v] == false && weight < key[v])
            {
                i++;
                key[v] = weight;
                min_heap.push(make_pair(weight, v));
                parent[v] = u;
            }
        }

    }

    // Print edges of MST using parent array
    for (int i = 1; i < V; i++) //as source does not have a parent
        printf("%d - %d\n", parent[i], i);

    cout << "i is " << i << endl;

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

