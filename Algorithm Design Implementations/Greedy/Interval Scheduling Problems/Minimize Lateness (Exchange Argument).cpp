/*

This is from section 5.2 from Algorithm Design. Psuedocode available there.

Resources used:
    -> for general overview of problem and simple (high-level) pseudocode: https://kartikkukreja.wordpress.com/2013/11/24/scheduling-to-minimize-lateness/
    -> for C++ implementation: https://github.com/kartikkukreja/blog-codes/blob/master/src/Scheduling%20to%20minimize%20lateness.cpp
            -> used their approach for operator overloading, instead of my usual qsort approach.

*/

#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <queue>

#include <algorithm>

using namespace std;

//can use qsort to sort, BUT will instead use operator overloading
struct Slot
{
    int length, deadline;

    bool operator<(const Slot& x) const
    {
        if (deadline != x.deadline)
        {
            return deadline < x.deadline;
        }
        else
        {
            return length < x.length;
        }
    }

};

int main()
{
    Slot slots[] = {{3,4},{5,6},{10,11},{1,3}};
    int n = sizeof(slots)/sizeof(slots[0]);

    sort(slots,slots+n); //slots + n is just pointer to nth element or, it can simply be, slots[n]

    int last_finished = 0, lateness = 0, temp;
    for(int i=0; i<n;i++)
    {
        temp = last_finished + slots[i].length;
        if(temp > slots[i].deadline)
        {
            if(temp-slots[i].deadline > lateness)
            {
                lateness=temp-slots[i].deadline;
            }
        }
        last_finished=temp;
    }

    cout << "Maximum lateness is " << lateness << "." << endl;


    return 0;
}


