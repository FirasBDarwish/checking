/*

This is based on section 5.4 from Algorithm Design.

Using: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

Another cool extensio from google's questions: https://www.youtube.com/watch?v=EaphyqKU4PQ
    -> does not check whether distance to node is less than current (shortest) distance to node 
        -> so has to add vector<bool> visited to check when a node has its shortest path considered 
            -> and check whether visited[u] is true when popping u from min_heap (as there may be more than one pairs for u in the min_heap,
            but the shortest one will naturally be popped first (due to min_heap, lowest key gets popped first, structure)).

*/

// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

typedef pair<int,int> iPair;

//adj is adjacency list, array of vectors of type pair<int,int>
    //can also be written as vector<pair<int,int>> adj[]
void addEdge(vector<pair<int,int>> *adj, int u, int v, int weight)
{
    adj[v].push_back(make_pair(u,weight));
    adj[u].push_back(make_pair(v,weight));

    return;
}

void shortest_path(vector<pair<int,int>> *adj, int V, int src)
{
    priority_queue <iPair, vector<iPair>, greater<iPair> > min_heap;

    /*
    priority_queue: This is the C++ Standard Library container class template that implements a priority queue.
    It is a type of container adapter that provides functionality for efficiently managing a collection of elements
    with priorities.

    <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>: This specifies the template arguments
    for the priority queue. It consists of three parts:

    pair<int, int>: This represents the type of elements that will be stored in the priority queue.
    In this case, it's a pair of integers.

    vector<pair<int, int>>: This specifies the underlying container type for the priority queue.
    A vector is used as the container to store the elements.

    greater<pair<int, int>>: This is a comparison function or functor used to determine the order
    of elements in the priority queue. The greater function object is used here, which will result
    in the elements being stored in ascending order based on the first element of the pair. If the
    first elements are equal, the second elements will be compared. This means the smallest pair
    will have the highest priority.
    */

    vector<int> dist(V, INF);

    min_heap.push(make_pair(0,src));
    dist[src] = 0;

    while(!min_heap.empty())
    {
        int u = min_heap.top().second; //gets vertices
        min_heap.pop();
        for (auto adjacent: adj[u])
        {
            int v = adjacent.first;
            int weight = adjacent.second;

            //this is the same as checking if v is in some vector visited
            //adding if visited[v] == false does not hurt, setting visited[v] = true would have to happen after line 62
            if(dist[u]+weight < dist[v]) //adjacent.second gets weight
            {
                dist[v] = dist[u]+weight;
                min_heap.push(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);

    return;

}

int main()
{

    int V = 9;
    vector<iPair> adj[V];
 
    // making above shown graph
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 0, 7, 8);
    addEdge(adj, 1, 2, 8);
    addEdge(adj, 1, 7, 11);
    addEdge(adj, 2, 3, 7);
    addEdge(adj, 2, 8, 2);
    addEdge(adj, 2, 5, 4);
    addEdge(adj, 3, 4, 9);
    addEdge(adj, 3, 5, 14);
    addEdge(adj, 4, 5, 10);
    addEdge(adj, 5, 6, 2);
    addEdge(adj, 6, 7, 1);
    addEdge(adj, 6, 8, 6);
    addEdge(adj, 7, 8, 7);
 
    shortest_path(adj, V, 0);

    return 0;
}