
/*
Using: https://www.geeksforgeeks.org/stable-marriage-problem/
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#define N 4 //number of men and women

// This function returns true if woman 'w' prefers man 'm1' over man 'm'
bool wPrefersM1OverM(int prefer[2*N][N], int w, int m, int m1)
{
    for (int i = 0; i<N; i++)
    {
        if(prefer[w][i] == m1)
            return true;

        if(prefer[w][i] == m)
            return false;
    }
    return true;
}

// Prints stable matching for N boys and N girls.
// Boys are numbered as 0 to N-1. Girls are numbered
// as N to 2N-1.
void stableMarriage(int prefer[2*N][N])
{
    // Stores partner of women. This is our output array that
    // stores passing information.  The value of wPartner[i]
    // indicates the partner assigned to woman N+i.  Note that
    // the woman numbers between N and 2*N-1. The value -1
    // indicates that (N+i)'th woman is free
    int wPartner[N];

    // An array to store availability of men.  If mFree[i] is
    // false, then man 'i' is free, otherwise engaged.
    bool mFree[N];

    // Initialize all men and women as free
    memset(wPartner, -1, sizeof(wPartner));
    memset(mFree, false, sizeof(mFree));
    int freeCount = N;

    // While there are free men
    while (freeCount > 0)
    {
        int free_ind = 0;
        while(mFree[free_ind] != false)
        {
            free_ind++;
        }

        int w_ind = 0;
        while(w_ind != N)
        {
            int w = prefer[free_ind][w_ind];

            if (wPartner[w-N] == -1)
                {
                    wPartner[w-N] = free_ind;
                    mFree[free_ind] = true;
                    freeCount--;
                    break;
                }
            else
            {
                if (wPrefersM1OverM(prefer, w, wPartner[w-N], free_ind))
                {
                    mFree[wPartner[w-N]] = false;
                    wPartner[w-N] = free_ind;
                    mFree[free_ind] = true;
                    break;
                }
            }
            w_ind++;
        }
    }

    // Print the solution
    cout << "Woman   Man" << endl;
    for (int i = 0; i < N; i++)
       cout << " " << i+N << "\t" << wPartner[i] << endl;
}

// Driver program to test above functions
int main()
{
    int prefer[2*N][N] = { {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
    stableMarriage(prefer);
 
    return 0;
}
