/*

This is from section 5.1 from Algorithm Design as extensions of the interval scheduling problem. Pseucode located there. 

Using STL priority_queue and, therefore, facing some issues when updating keys and what not.
Attempting to use: https://github.com/kartikkukreja/blog-codes/blob/master/src/Interval%20Partitioning%20Problem.cpp
and  (related)
and some theory from https://stumash.github.io/Algorithm_Notes/greedy/intervals/intervals.html
BUT heavily diverted from what is included in these resources..

*/

#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <queue>

#include <iostream>
#include <queue> //implements priority queue (pretty much binary heap) with maxheap so we have to do minheap

using namespace std;

//can use qsort to sort 
struct Slot
{
    int start;
    int end;
};

//sorting by start-time
// documentation for compare function: https://www.programiz.com/cpp-programming/library-function/cstdlib/qsort
int compare(const void* a, const void* b)
{
    Slot* slot1 = (Slot *)a, *slot2 = (Slot *)b;
    if(slot1->start != slot2->start)
        return slot1->start - slot2->start; //returns negative value if first argument is < second argument,
                                        //positive value if first argument is > second argument,
                                        //0 if first argument == second argument
    return slot1->end - slot2->end; //if starttimes are equal, then sort by end-times
}

int main()
{
    Slot slots[]= {{1, 2}, {1, 4}, {1, 2}, {2, 4}, {2, 7}, {6, 9}, {6,9}, {8,11}, {9,11}, {10,11}};
    
    // for (int i=0; i<sizeof(slots)/sizeof(slots[0]); i++)
    //     {
    //         cout << "Element from " << slots[i].start << " to " << slots[i].end << endl;
    //     }

     //sorting by start-time
    int n = sizeof(slots)/sizeof(slots[0]);
    qsort(slots, n, sizeof(Slot), compare); //see documentaton

    // cout << "------" << endl;
    // for (int i=0; i<sizeof(slots)/sizeof(slots[0]); i++)
    // {
    //     cout << "Element from " << slots[i].start << " to " << slots[i].end << endl;
    // }

    // defining priority queue
    priority_queue<int> pq;

    int d=0, j; //tracking number of resources
    int* schedule = new int[n];

    schedule[0] = 0;
    pq.push(-1*slots[0].end);

    for(int i=1;i<n;i++)
    {
        j=pq.top();
        if(-slots[i].start <= j)
        {
            pq.pop();
            pq.push(-1*slots[i].end);
        }
        else
        {
            d++;
            pq.push(-1*slots[i].end);
        }
    }
    
    cout << "Depth needed is " << d+1 << " resources." << endl;

}