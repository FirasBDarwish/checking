/* 

This is based on section 3.3 from Algorithm Design.

using: https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/

related (but not used): https://www.geeksforgeeks.org/dfs-traversal-of-a-tree-using-recursion/
overview of STL map: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/

O(V+E), where V is the number of nodes and E is the number of edges.

*/

// C++ program to print DFS traversal from
// a given vertex in a  given graph
#include <bits/stdc++.h>
using namespace std;
 
// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
    public:
    map<int, bool> visited;
    map<int,list<int>> adj; //potentially substitute list<int> with vector<int>

    // Function to add an edge to graph
    void addEdge(int v, int w);
 
    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
    // Add w to v’s list.
    adj[v].push_back(w);

    return;
}

void Graph::DFS(int v)
{
    visited[v] = true;
    cout << v << " ";

    for(auto adjacent: adj[v])
    {
        if(visited[adjacent] != true)
        {
            visited[adjacent] == true;
            DFS(adjacent);
        }
    }

    return;

}

// Driver code
int main()
{
    // Create a graph given in the above diagram
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n";
 
    // Function call
    g.DFS(2);
 
    return 0;
}

