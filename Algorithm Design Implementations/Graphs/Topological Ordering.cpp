/*

From section 3.6 of Algorithm Design.

Using: https://www.geeksforgeeks.org/cpp-program-for-topological-sorting/

Note: topological ordering takes advantage of the idea of DFS, but its implementation
and--especially--use of the stack is slightly different.

*/

// A C++ program to print topological sorting of a DAG
#include <iostream>
#include <list>
#include <stack>
#include<bits/stdc++.h>
using namespace std;
 
// Class to represent a graph
class Graph {
    int V; // No. of vertices'
 
    // Pointer to an array containing adjacency listsList
    list<int>* adj;
 
    // // A function used by topologicalSort
    // void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);

    public:
    Graph(int V); // Constructor
 
    // function to add an edge to graph
    void addEdge(int v, int w);
 
    // prints a Topological Sort of the complete graph
    void topologicalSort();

    //used by topologicalSort()
    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &stack);

};

Graph::Graph(int V)
{
    this->V = V;
    this->adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);

    //add the following line if you want to have an undirected graph.
    //adj[w].push_back(v);
}

void Graph::topologicalSortUtil(int v, vector<bool> &visited, stack<int> &stack)
{
    visited[v] = true;
    for(auto adjacent: adj[v])
    {
        if(visited[adjacent] != true)
        {
            visited[adjacent] = true;
            topologicalSortUtil(adjacent, visited, stack);
        }
    }

    //stack used in a unique way so that the element with no adjacent nodes is the first in (so last out).
    stack.push(v);
    
    return;
}

void Graph::topologicalSort()
{
    //make data structures
    vector<bool> visited(V, false);
    stack<int> stack;

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one

    //this for loop is important as it allows you to cover any islands that are not connected.
    //it also means your base node is going to be node 0 and that you go through every point to make topological ordering.
    for (int i = 0; i < V; i++)
        if (visited[i] != true)
            topologicalSortUtil(i, visited, stack);

//IMPORTANT: if you use the following, you will pretty much be conducting DFS on that one node. 
    // topologicalSortUtil(5, visited, stack);

    //print stack using stack structure (those who have no directed edge to some other node are last to be outputted)
    while(!stack.empty())
    {
        cout << stack.top() << " ";
        stack.pop();
    }

    return;
}

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
 
    cout << "Following is a Topological Sort of the given graph: ";
    g.topologicalSort();
 
    return 0;
}
