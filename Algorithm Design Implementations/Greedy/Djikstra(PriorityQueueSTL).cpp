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