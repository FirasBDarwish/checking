

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


