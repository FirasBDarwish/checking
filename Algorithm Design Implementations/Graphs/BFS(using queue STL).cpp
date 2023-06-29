/*

This is based on section 3.3 from Algorithm Design.

Primary source used here: https://www.geeksforgeeks.org/bfs-using-stl-competitive-coding/

O(V+E), where V is the number of nodes and E is the number of edges.

*/

// A Quick implementation of BFS using
// vectors and queue
#include <bits/stdc++.h>
#define pb push_back
 
using namespace std;
 
vector<bool> v;
vector<vector<int> > g;

void edge(int a, int b)
{
    g[a].push_back(b);
    
    // for undirected graph add this line
    // g[b].pb(a);

    return;
}

void BFS(int u)
{
    queue<int> q;

    q.push(u);
    v[u] = true;

    while(!q.empty())
    {
        u = q.front();
        q.pop();
        cout << u << " ";

        for(auto adjacent: g[u])
        {
            if(v[adjacent] == false)
            {
                q.push(adjacent);
                v[adjacent] = true;
            }
            else
            {
                continue;
            }
        }
    }

    return;
}


// Driver code
int main()
{
    int n, e;
    cout << "input number of nodes, followed by the number of edges" << endl;
    cin >> n >> e;
 
    v.assign(n, false);
    g.assign(n, vector<int>());
 
    cout << "input the requsted number directed edges as 1 2 (followed by enter) to indicate directed edge from node 1 to node 2" << endl;
    int a, b;
    for (int i = 0; i < e; i++) {
        cin >> a >> b;
        edge(a, b);
    }

    // for (int i = 0; i < n; i++) {
    //     if (!v[i])
    //         BFS(i);
    // }
 
    int u;
    cin >> u;
    BFS(u);
 
    return 0;
}
