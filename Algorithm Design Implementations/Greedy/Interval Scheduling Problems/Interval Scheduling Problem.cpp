/*

This is from section 5.1 from Algorithm Design. Pseucode located there. 

Brief follow up on qsort (used here): https://en.cppreference.com/w/cpp/algorithm/qsort
Documentations for qsort (as well as what compare function does): https://www.programiz.com/cpp-programming/library-function/cstdlib/qsort

Reference code (but has alternative approach) for solving this problem in C++: https://github.com/kartikkukreja/blog-codes/blob/master/src/Interval%20Scheduling%20Problem.cpp
    -> instead of qsort, uses operator overriding in inteval class--very clever

*/

#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <queue>

using namespace std;

//can use qsort to sort 
struct Slot
{
    int start;
    int end;
};

// documentation for compare function: https://www.programiz.com/cpp-programming/library-function/cstdlib/qsort
int compare(const void* a, const void* b)
{
    Slot* slot1 = (Slot *)a, *slot2 = (Slot *)b;
    if(slot1->end != slot2->end)
        return slot1->end - slot2->end; //returns negative value if first argument is < second argument,
                                        //positive value if first argument is > second argument,
                                        //0 if first argument == second argument
    return slot1->start - slot2->start;
}

queue<int> scheduled(Slot *slots, int n)
{
    queue<int> scheduled;
    int at_time=0;
    for(int i=0; i<n; i++)
    {
        if(slots[i].start >= at_time)
        {
            scheduled.push(i);
            at_time = slots[i].end;
        }
    }

    return scheduled;

} 

int main()
{
    Slot slots[]= {{1, 3}, {2, 3}, {2, 5}, {6, 7}, {3, 4}, {3, 5}};
    // for (int i=0; i<sizeof(slots)/sizeof(slots[0]); i++)
    // {
    //     cout << "Element from " << slots[i].start << " to " << slots[i].end << endl;
    // }

    //sorting
    int n = sizeof(slots)/sizeof(slots[0]);
    qsort(slots, n, sizeof(Slot), compare); //see documentaton

    queue<int> scheduled_q = scheduled(slots, n);

    int index;
    while(!scheduled_q.empty())
    {
        index = scheduled_q.front();
        cout << "Element from " << slots[index].start << " to " << slots[index].end << endl;
        scheduled_q.pop();
    }

    return 0;


    // cout << "----------------------------" << endl;
    // for (int i=0; i<sizeof(slots)/sizeof(slots[0]); i++)
    // {
    //     cout << "Element from " << slots[i].start << " to " << slots[i].end << endl;
    // }

    // cout << slots[0].start << endl; //indexing
    // cout << sizeof(slots) / sizeof(slots[0]) << endl; //always works
    // cout << sizeof(slots) << endl; //size of array in bits
} 



