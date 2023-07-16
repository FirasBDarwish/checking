
/*

This is an implementation from section 6.8 from Algorithm Design. 

*/

#define INFINITY_byFiras 100000

#include <bits/stdc++.h>
#include <math.h>
#include <climits>
using namespace std;

typedef pair<int,int> iPair;

//adj is adjacency list, array of vectors of type pair<int,int>
    //can also be written as vector<pair<int,int>> adj[]
void addEdge(vector<pair<int,int>> *adj, int u, int v, int weight)
{
    adj[u].push_back(make_pair(v,weight));

    return;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int minCost(vector<pair<int,int>> *adj, int s, int t, int V)
{
    //M[0,...,n-1][V] rows: number of edges (0, 1, 2, 3, 4, 5, 6), column: starting node (a, b, c, d, e, t)
    int M[V][V];
    for(int i=0;i<V;i++)
    {
        // M[t][i] = 0; //going from t to itself is a cost of 0 regardless the number of permitted edges 
        // M[i][0] = 100; //infinity

        M[0][i] = INFINITY_byFiras;
        M[i][t] = 0;
    }

    int compare = INFINITY_byFiras;
    for(int j=1; j<V; j++)
    {
        for(int i=0; i<V; i++)
        {
            if(i==t)
            {
                continue;
            }
            int min_1 = INFINITY_byFiras;
            for(auto adjacent: adj[i]) //!
            {
                compare = M[j-1][adjacent.first] + adjacent.second;
                min_1 = min(min_1, compare);
            }
            M[j][i] = min(min_1,  M[j-1][i]);
            cout << "(" << j << "," << i << "): " << M[j][i] << endl;
        }
    }

    return M[V-1][s];

}

int main()
{

    int V = 6;
    vector<iPair> adj[V];
 
    // making above shown graph //should be 10
    addEdge(adj, 0, 1, -4);
    // addEdge(adj, 1, 3, -1);
    addEdge(adj, 3, 0, 6);
    addEdge(adj, 0, 5, -3);
    addEdge(adj, 2, 1, 8);
    addEdge(adj, 4, 2, -3);
    addEdge(adj, 1, 4, -2);
    addEdge(adj, 1, 3, -1);
    addEdge(adj, 3, 5, 4);
    addEdge(adj, 4, 5, 2);
    addEdge(adj, 2, 5, 3);
 
    //src is 0, end is 5
    cout << "The minimum cost is " << minCost(adj, 0, 5, V) << endl;

    return 0;

}
