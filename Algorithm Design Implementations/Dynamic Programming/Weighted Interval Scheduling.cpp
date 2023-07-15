/*

 Based on section 6.1 from Algorithm Design, runs in O(nlog(n)). Book suggests
 it runs in O(n) because it assumes input intervals are sorted by finish time. We use
 quick sort (as part of sort() algorithm method) to sort our array, which is O(nlogn)
 O(nlogn + n) = O(nlogn)

 Using: https://www.geeksforgeeks.org/weighted-job-scheduling-log-n-time/

 -> implemented printing mechanism to show final slots/jobs in optimal solution

Note: this input includes memoization (using table array!, check)

sort() can have a third parameter passed in that determines how sorting is done or
you can operator overload < in the struct/class being used and not have to pass
that third parameter

Find the maximum profit subset of jobs such that no two jobs in the subset overlap

*/

#include <iostream>
#include <algorithm>
using namespace std;

//profit is the same thing as the weight
struct Job
{
    int start, finish, profit;
};

//sort according to finish time
    //used as third parameter for sort (see note in header)
bool myfunction(Job s1, Job s2)
{
    return (s1.finish < s2.finish);
}

//A binary search based function to find the latest job (before current job) that doesn't conflict with current job.
//index is index of the current job.
int binarySearch(Job *jobs, int index)
{
    int lo = 0, hi = index - 1;
    while(lo <= hi)
    {
        int mid = (lo + hi)/2; //lo never updated (stays at 0, so lo + (lo+hi)/2 not needed here)
        if(jobs[mid].finish <= jobs[index].start)
        {
            if(jobs[mid+1].finish <= jobs[index].start)
            {
                lo = mid+1;
            }
            else
            {
                return mid;
            }
        }
        else
        {
            hi = mid - 1;
        }

    }

    return -1;

}

int findMaxProfit(Job *arr, int n)
{
    sort(arr, arr+n, myfunction);

    //table for memoization (store solutions of subproblems)
    int* table = new int[n]; //1D array of size n
    table[0] = arr[0].profit;

    //filling in table for each call
    for(int i=1; i<n; i++)
    {
        int inclProf = arr[i].profit;
        int l = binarySearch(arr, i);
        if (l != -1)
        {
            inclProf += table[l];
        }

        table[i] = max(inclProf, table[i-1]);

    }

    //this is used to print out solution 
    for(int i=n-1;i>=0;i--)
    {
        int inclProf = arr[i].profit;
        int l = binarySearch(arr, i);
        if (l != -1)
        {
            inclProf += table[l];
        }

        //if max(inclProf, table[i-1]) is inclProf, then j is in our optimal solution.
        if(inclProf > table[i-1])
        {
            cout << i << endl;
            i = l+1; //because it decrements itself
            continue;
        }
        //else table[i-1] is greater than inclProf and inclProf is not in optimal solution
            //-> so go to the next index. 

    }

    int result = table[n-1];
    delete[] table;

    cout << "Optimal profit is " << result << endl;
    return result;

}

int main()
{
    
    Job arr[] = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Intervals in optimal solution (once ordered based on finish time): " << endl;

    int result = findMaxProfit(arr, n);
    return 0;

}
