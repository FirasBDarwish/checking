/*

From section 6.3 from Algorithm Design. Time Complexity: O(N * W). where ‘N’ is the number of elements and ‘W’ is capacity. 
Auxiliary Space: O(N * W). The use of a 2-D array of size ‘N*W’.

using: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
Specifically: Overlapping Sub-problems Property Approach for 0/1 Knapsack Problem using Dynamic Programming

Goal is to: We are given N items where each item has some weight and profit associated with it.
We are also given a bag with capacity W, [i.e., the bag can hold at most W weight in it].
The target is to put the items into the bag such that the sum of profits associated with them
is the maximum possible. 

*/

// A dynamic programming based
// solution for 0-1 Knapsack problem
#include <bits/stdc++.h>
using namespace std;

int max(int a, int b)
{
    return (a > b) ? a : b; //if a > b, return a, if a !> b, return b;
}

//wt holds the weights of each edge, val holds the profit gained from each edge
//NOTE how: wt and val are of size (0,1,2,3...,n-1), while K adds an extra 0th layer to row and column
//but does not zero index.
int knapSack(int W, int *wt, int *val, int n)
{
    vector<vector<int>> K(n+1, vector<int>(W+1)); //each of the n+1 vectors (to include 0) will be filled with a vector<int> of size W+1 (to include 0)

    //to go from [0,n]
    for(int i=0; i<=n; i++)
    {
        //to go from [0,W], current available capacity 
        for(int j=0; j<=W; j++)
        {
            if(i == 0 || j == 0)
            {
                K[i][j] = 0;
            }
            //if weight of current index 
            else if(wt[i-1] <= j)
            {
                K[i][j] = max(K[i-1][j], val[i-1] + K[i-1][j - wt[i-1]]);
                                                            //adjusting weight
            }
            else
            {
                K[i][j] = K[i-1][j]; //weight as it is 
            }
        }
    }

    return K[n][W];

}

// Driver Code
int main()
{
    int profit[] = { 60, 100, 120 };
    int weight[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(profit) / sizeof(profit[0]);
 
    cout << knapSack(W, weight, profit, n) << endl;
 
    return 0;
}