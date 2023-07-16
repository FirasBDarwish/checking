
/*

This is an implementation of section 6.6 from Algorithm Design.

Using: https://www.geeksforgeeks.org/sequence-alignment-problem/
    -> changed: size of DP from n+m+1 x n+m+1 to m+1 x n+1 (like book implementation)
    -> changed: logic for finding id (which is the index that cuts out 'leading underscores from our printed format)
        so  _______abc
        and ______wxyz
            become:
                _abc
                wxyz
*/

#include <bits/stdc++.h>
 using namespace std;

 int min(int a, int b, int c)
 {
    int min = a;
    
    if(min > b)
    {
        min = b;
    }
    if(min > c)
    { 
        min = c;
    }

    return min;
 }

// function to find out the minimum penalty
void getMinimumPenalty(string x, string y, int pxy, int pgap)
{
    int m = x.length();
    int n = y.length();

    int dp[m+1][n+1]; //changed from source code 

    //initializing
    for(int i=0; i<m+1; i++)
    {
        dp[i][0] = i*pgap;
    }
    for(int i=0; i<n+1;i++)
    {
        dp[0][i] = i*pgap;
    }

    //finding minimum pen alty
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(x[i-1] == y[j-1]) //i=1 -> x[0]
            {
                dp[i][j] = dp[i-1][j-1]; // + alpha_xy (which is 0 here as they are the same character)
            }
            else
            {
                dp[i][j] = min(pxy + dp[i-1][j-1], pgap + dp[i-1][j], pgap + dp[i][j-1]);
            }
        }

    }

    int l = n + m;
    int i = m, j = n;
    int xpos = l, ypos = l;

        //both go from to 0 to n + m
    int xans[l+1], yans[l+1];

            //ran through m (for i) (so i went from m to 1 which transaltes to m-1 to 0 in x, which is all that that array holds)
    while (! (i == 0 || j == 0)) //ran through n (for j)
    {
            //x goes from 0 to m-1, y goes from 0 to n-1
        if(x[i-1] == y[j-1])
        {
            xans[xpos--] = (int)x[i-1]; //used index xpos then decrement it
            yans[ypos--] = (int)y[j-1];
            i--;
            j--;
        }
        else if (dp[i-1][j-1] + pxy == dp[i][j])
        {
            xans[xpos--] = (int)x[i-1]; //used index xpos then decrement it
            yans[ypos--] = (int)y[j-1]; // casting with (int)
            i--;
            j--;
        }
        else if (dp[i-1][j] + pgap == dp[i][j])
        {
            xans[xpos--] = (int)x[i-1];
            yans[ypos--] = (int)'_';
            i--;
        }
        else
        {
            xans[xpos--] = (int)'_';
            yans[ypos--] = (int)y[j-1];
            j--;
        }

    }
    while(xpos > 0)
    {
        if(i > 0)
        {
            xans[xpos--] = (int)x[i-1];
            i--;
        }
        else
        {
            xans[xpos--] = (int)'_';
        }
    }
    while(ypos > 0)
    {
        if(j > 0)
        {
            yans[ypos--] = (int)y[j-1];
            j--;
        }
        else
        {
            yans[ypos--] = (int)'_';
        }
    }

    int id=1; //as we never use xans[0] as xans goes from 0 to l (=n+m) so we can just use 1 to l to hold values
    while(1)
    {
        if((char)xans[id] != '_' || (char)yans[id] != '_' )
        {
            break;
        }
        id++;
    }

    cout << "Minimum Penalty in aligning the genes = ";
    cout << dp[m][n] << "\n";
    cout << "The aligned genes are :\n";
    
    //print final answer
    cout << "X: ";
    for(int i=id; i<l+1; i++)
    {
        cout << (char)xans[i];
    }
    cout << endl;
    cout << "Y: ";
    for(int i=id; i<l+1; i++)
    {
        cout << (char)yans[i];
    }

    return;

}

// Driver code
int main(){
    // input strings
    string gene1 = "AGGGCT";
    string gene2 = "AGGCA";
     
    // initialising penalties of different types
    int misMatchPenalty = 3;
    int gapPenalty = 2;
 
    // calling the function to calculate the result
    getMinimumPenalty(gene1, gene2,
        misMatchPenalty, gapPenalty);
    return 0;
}