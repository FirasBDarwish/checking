/*

This is from section 5.1 from Algorithm Design as extensions of the interval scheduling problem. Pseucode located there. 

Primarily using: https://github.com/kartikkukreja/blog-codes/blob/master/src/Interval%20Partitioning%20Problem.cpp

Okay, so a lot of things happening here. I followed the tutorial above but chose to follow the priority_queue model
I created earlier in the file BinaryHeap.cpp as it is more intuitive. This github page referenced above does something
very odd: it creates a heap array (which contains the 'index' in each position of the priority queue); using this index,
you can query the key of the element in the heap. It is a very convoluted and unnecessarily complicated architecture
for this question.

Instead, I've modified the binary heap structure used so that there is a primary array of type class resource_user.
Each instantiation of resource_user holds a key (int, which will continue to be used for heapify up AND heapify down
as well as extracting min and what not) as well as a resource (int, which simply tells us which resource that element
of the heap 'represents'). This pushed me to then make a extract_resource() function which returns the resource
of the element in the heap with the min_value (so lowest key). The logic of the main function is the following:
if a slot's (slot A) start time is after or at the end of the earliest-ending, already-booked slot (slot B), then we
can assign the resource given to slot B to slot A ('passing' that resource, in some way). Otherwise, we create a new
resource and uniquely assign it slot A.


*/

//using code in Binary Heap.cpp

// A C++ program to demonstrate common Binary Heap Operations
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <queue>

#include<iostream>
#include<climits>
using namespace std;

struct resource_user
{
    int key;
    int resource;

};

//swaps the values of x and y so that the index that contains x now contains y and vice versa
void swap(resource_user* x, resource_user* y)
{
    resource_user temp = *x;
    *x = *y;
    *y = temp;

    return;
}

//implementing mean-heap (as max-heap is given using the priority queue C++ class)
class MinHeap
{
    private:
        resource_user *harr; // pointer to array of elements in heap
        int capacity; // maximum possible size of min heap
        int heap_size; // Current number of elements in min heap

    public:
        // Constructor
        MinHeap(int capacity);

        // to heapify a subtree with the root at given index
        void MinHeapify(int index);

        int parent(int i) { return (i-1)/2; }
        int left(int i) { return i*2+1; } //indexing starting with 0
        int right(int i) { return i*2+2; } //indexing starting with 0

        // to extract the root which is the minimum element
        int extractMin();

        //to extract the resource which the minimum element uses
        int extractResource();
    
        // Decreases key value of key at index i to new_val
        void decreaseKey(int i, int new_val);
    
        // Returns the minimum key (key at root) from min heap
        int getMin() { return harr[0].key; }
    
        // Deletes a key stored at index i
        void deleteKey(int i);
    
        // Inserts a new key 'k'
        void insertKey(int resource, int k);

        void print()
        {
            cout << "Min_Heap: ";
            for(int i=0; i<heap_size;i++)
            {
                cout << harr[i].key << " ";
            }
            cout << endl;
        }

        ~MinHeap()
        {
            delete[] harr;
        }
};

void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();

    return;
}

int MinHeap::extractResource()
{
    if(heap_size <= 0)
    {
        cout << "There are currently no elements in the heap to extractResource." << endl;
        return 0;
    }
    else if(heap_size == 1)
    {
        return harr[0].resource;
    }
    else
    {
        int root = harr[0].resource;
        return root;
    }
}

int MinHeap::extractMin()
{
    if(heap_size <= 0)
    {
        cout << "There are currently no elements in the heap to extractMin." << endl;
        return 0;
    }
    else if(heap_size == 1)
    {
        heap_size--;
        return harr[0].key;
    }
    else
    {
        int root = harr[0].key;
        harr[0] = harr[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }
}

void MinHeap::MinHeapify(int index)
{
    int l = left(index);
    int r = right(index);
    int smallest = index;

    if(l < heap_size && harr[smallest].key > harr[l].key)
        smallest = l;
    if(r < heap_size && harr[smallest].key > harr[r].key)
        smallest = r;
    if(smallest != index)
        {
            swap(&harr[index], &harr[smallest]);
            MinHeapify(smallest);
        }
   
    return;
}

void MinHeap::decreaseKey(int i, int new_val)
{
    if(heap_size == 0)
    {
        cout << "There are no elements in the Binary Heap. Cannot decrease key." << endl; 
    }
    else if(i > heap_size-1 || i < 0)
    {
        cout << "Index to decrease key does not exist." << endl;
    }
    else if(new_val < harr[i].key)
    {
        harr[i].key = new_val;

        //heapify_up
        while(i != 0 && harr[parent(i)].key > harr[i].key)
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
    else
    {
        //if new value is greater than old value
        harr[i].key = new_val;
        MinHeapify(i); //heapify_down
    }
    return; 
}

MinHeap::MinHeap(int capacity)
{
    if(capacity <= 0)
    {
        cout << "We advise you input a positive integer for capacity." << endl;
        return; 
    }
    this->capacity = capacity;
    this->heap_size = 0;
    this->harr = new resource_user[capacity];
    return;
}

void MinHeap::insertKey(int resource, int k)
{
    if(heap_size == capacity)
    {
        cout << "The binary heap is full. Cannot insertKey." << endl;
    }
    else
    {
        harr[heap_size].key = k;
        harr[heap_size].resource = resource;

        int i = heap_size;
        while(i != 0 && harr[parent(i)].key > harr[i].key)
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }

        // cout << harr[parent(i)] << endl;
        heap_size++;
    }
    
    return;
}

//---------------ARCHITECTURE FOR SORTING--------------
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
//-----------------------------------------------------

int main()
{

    Slot slots[]= {{1, 2}, {1, 4}, {1, 2}, {2, 4}, {2, 7}, {6, 9}, {6,9}, {8,11}, {9,11}, {10,11}};

     //sorting by start-time
    int n = sizeof(slots)/sizeof(slots[0]);
    qsort(slots, n, sizeof(Slot), compare); //see documentaton

    MinHeap h(n);

    int* schedule = new int[n];
    int d = 0, j;
    schedule[0] = 0;
    
    h.insertKey(d, slots[0].end);

    for(int i=1; i<n; i++)
    {
        j = h.extractResource();
        h.print();
        if(slots[i].start >= (h.getMin()))
        {
            schedule[i] = j;
            h.extractMin();
            h.insertKey(j,slots[i].end);
        }
        else
        {
            d++;
            schedule[i] = d;
            h.insertKey(d,slots[i].end);
        }
    }

    cout << "The minimum number of resources needed is " << d+1 << "." << endl;
    for(int i=0; i<n; i++)
    {
        cout << "The slot that starts at " << slots[i].start << " and ends at " << slots[i].end << " is scheduled for resource " << schedule[i] << "." << endl;
    }


}