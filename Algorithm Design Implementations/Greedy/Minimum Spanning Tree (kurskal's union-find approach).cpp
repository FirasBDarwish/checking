/*

This is from section 5.5 of Algorithm Design.

More information on disjoint sets: https://people.cs.georgetown.edu/jthaler/ANLY550/lec6.pdf

*/

// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include<bits/stdc++.h>
using namespace std;
  
// Creating shortcut for an integer pair
typedef pair<int, int> iPair;
  
// Structure to represent a graph
struct Graph
{
    int V, E;
    vector< pair<int, iPair> > edges; //vector of type pair<int, pair<int,int>>
  
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w)
    {
                        //same as make_pair(w, make_pair(u,v))
        edges.push_back({w, {u,v}}); //don't need to do edges[u].push_back(make_pair(w, make_pair(u,v)))
                                    //as we don't care about adjacency list representation
                                    //(why should we care about adjacents in kurskal approach?)
    }

    int kruskalMST();

};

struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        this->n=n;

        parent = new int[n+1];
        rnk = new int[n+1];

        for(int i=0; i<=n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }

    }

    int find(int u)
    {
        if (u != parent[u])
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int x, int y)
    {
        x=find(x);
        y=find(y);

        /* Make tree with smaller height
        a subtree of the other tree */
        if(rnk[x] > rnk[y])
        {
            parent[y] = x; //which is the greater rank
        }
        else //if rnk[x] <= rnk[y]
        {
            parent[x] = y; //which is the greater rank
        }

        if(rnk[x] == rnk[y])
        {
            rnk[y]++; //if they are the same, increase rank of y as parent[x] will still become = y
        }


    }

};

/* Functions returns weight of the MST*/
int Graph::kruskalMST()
{

    int mst_weight = 0;

    // Sort edges in increasing order on basis of cost (weight/first-element)
    sort(edges.begin(),edges.end());

    DisjointSets ds(V);

    for(auto edge: edges)
    {
        int u = edge.second.first;
        int v = edge.second.second;

        int set_u = ds.find(u); //get first parent
        int set_v = ds.find(v); //get first parent

        //checkin if it forms a cycle
        if(set_u != set_v)
        {
            cout << u << " - " << v << endl;

            mst_weight += edge.first;

            ds.merge(set_u, set_v);
        }
    }

    return mst_weight;

}

// Driver program to test above functions
int main()
{
    /* Let us create above shown weighted
    and undirected graph */
    int V = 9, E = 14;
    Graph g(V, E);
  
    // making above shown graph
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
  
    cout << "Edges of MST are \n";
    int mst_wt = g.kruskalMST();
  
    cout << "\nWeight of MST is " << mst_wt << endl;
  
    return 0;
}