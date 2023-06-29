// An Iterative C++ program to do DFS traversal from
// a given source vertex. DFS(int s) traverses vertices
// reachable from s.
#include<bits/stdc++.h>
using namespace std;
 
// This class represents a directed graph using adjacency
// list representation
class Graph
{
    private:
    int V; //number of vertices
    list<int> *adj; //adjacency list, pointer to list<int>

    public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w); // to add an edge to graph
    void DFS(int s);  // prints all vertices in DFS manner
    // from a given source

};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V]; //dynamically allocated array of type list<int> so that each element is of type list<int>
    
    //can resize each element (which is of type list<int>) to V (so that we effectively have a 2D array)
    // for(int i=0; i<V; i++)
    // {
    //     adj[i].resize(V);
    // }
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
   //if undirected graph, uncomment what's below
    //adj[w].push_back(v);

    return;
}

void Graph::DFS(int s)
{
    vector<bool> visited(V, false);

    stack<int> stack;
    stack.push(s);
    visited[s] = true;

    while(!stack.empty())
    {
        s = stack.top();
        stack.pop();
        cout << s << " ";
        for(auto adjacent: adj[s])
        {
            if(visited[adjacent] != true)
            {
                visited[adjacent] = true;
                stack.push(adjacent);
            }
        }
    }
    return; 
}

// Driver program to test methods of graph class
int main()
{
    Graph g(4);  // Total 4 vertices in graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Depth First Traversal\n";
    g.DFS(2);
 
    return 0;
}