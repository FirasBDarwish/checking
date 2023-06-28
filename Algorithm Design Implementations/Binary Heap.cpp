/*
Section 2.5 of Algorithm Design (more explanations for heapify-up and heapify-down with psuedocode)

Binary Heap using: https://www.geeksforgeeks.org/binary-heap/
Priority queue using binary heap: https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
This second link is very similar to binary heap as binary heap as a structure works well with the motivation behind priority queues.

Idea behind heapify_up and heapify_down here (both necessary in BINARY HEAP): https://pages.cs.wisc.edu/~mcw/cs367/lectures/heaps.html

How heapify_down plays a role in heapsort: https://www.geeksforgeeks.org/heap-sort/

*/

// A C++ program to demonstrate common Binary Heap Operations
#include<iostream>
#include<climits>
using namespace std;

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;

    return;
}

//implementing mean-heap (as max-heap is given using the priority queue C++ class)
class MinHeap
{
    private:
        int *harr; // pointer to array of elements in heap
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
    
        // Decreases key value of key at index i to new_val
        void decreaseKey(int i, int new_val);
    
        // Returns the minimum key (key at root) from min heap
        int getMin() { return harr[0]; }
    
        // Deletes a key stored at index i
        void deleteKey(int i);
    
        // Inserts a new key 'k'
        void insertKey(int k);

        void print()
        {
            cout << "Min_Heap: ";
            for(int i=0; i<heap_size;i++)
            {
                cout << harr[i] << " ";
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
        return harr[0];
    }
    else
    {
        int root = harr[0];
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

    if(l < heap_size && harr[smallest] > harr[l])
        smallest = l;
    if(r < heap_size && harr[smallest] > harr[r])
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
    else if(new_val < harr[i])
    {
        harr[i] = new_val;

        //heapify_up
        while(i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
    else
    {
        harr[i] = new_val;
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
    this->harr = new int[capacity];
    return;
}

void MinHeap::insertKey(int k)
{
    if(heap_size == capacity)
    {
        cout << "The binary heap is full. Cannot insertKey." << endl;
    }
    else
    {
        harr[heap_size] = k;

        int i = heap_size;
        while(i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }

        // cout << harr[parent(i)] << endl;
        heap_size++;
    }
    
    return;
}

// Driver program to test above functions
int main()
{
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.print();
    h.deleteKey(1);
    h.print();
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    h.print();
    cout << h.extractMin() << " ";
    h.print();
    cout << h.getMin() << " ";
    h.print();
    //works if we are changing key to something lower than what it was
    h.decreaseKey(2, 1);
    h.print();
    cout << h.getMin();
    h.print();

    //works if we are changing key to something greater than what it was
    h.decreaseKey(1,50);
    h.print();
    return 0;
}