/*

This is based on section 3.3 from Algorithm Design. This implementation uses queues (in the datastructure list).

Using the following link for main reference: https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
As a back-up (but was NOT used): https://www.techiedelight.com/breadth-first-search/ 

O(V+E), where V is the number of nodes and E is the number of edges.


BFS.cpp uses vector<list<int>>, BFS(using queue STL) uses vector<vector<int>>; difference between list and vector is described
here: https://stackoverflow.com/questions/2209224/vector-vs-list-in-stl

*/

// C++ code to print BFS traversal from a given
// source vertex
 
#include <bits/stdc++.h>
using namespace std;
 
// This class represents a directed graph using
// adjacency list representation
class Graph {
    private:
    int V; //number of vertices
    vector<list<int>> adj; //adjacency list

    public:
    // Constructor
    Graph(int V);
 
    // Function to add an edge to graph
    void addEdge(int v, int w);
 
    // Prints BFS traversal from a given source s
    void BFS(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    this->adj.resize(V);
}

//indexed from 0 to V-1
void Graph::addEdge(int v, int w)
{
    if(v < 0 || v > V-1 || w < 0 || w > V-1)
    {
        cout << "Index provided outside of range of graph vertices. Cannot addEdge. ";
    }
    else
    {
        adj[v].push_back(w);
        //adj[w].push_back(v); //add if undirected graph, currently v is source and w is connected vertice (bridge from v -> w)
    }
    return;
}

void Graph::BFS(int s)
{
    //mark all vertices as not visited
    vector<bool> visited;
    visited.resize(V, false);

    // Create a queue for BFS
    list<int> queue;

    visited[s] = true;
    queue.push_back(s);

    while(!queue.empty())
    {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s.
        // If an adjacent has not been visited,
        // then mark it visited and enqueue it
        for (auto adjacent: adj[s])
        {
            //To note adjacency list ordering
            //cout << "Adjacent to " << s << " is " << adjacent << endl;
            if(visited[adjacent] == true)
                continue;
            else
            {
                queue.push_back(adjacent);
                visited[adjacent] = true;
            }
        }
    }

}

// Driver code
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);
 
    return 0;
}