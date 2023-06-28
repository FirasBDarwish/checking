/*

From Section 2.5 of Algorithm Design.
This is based on: https://www.geeksforgeeks.org/heap-sort/
O(n*log(n))

Note: Can pass vector by reference (&) instead of passing dynamically allocated array to function.
*/

// C++ program for implementation of Heap Sort (ascending/descending order, depending on choice of heapify)

#include <iostream>
using namespace std;

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap

void heapify(int *arr, int N, int i)
{
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left < N && arr[largest] < arr[left])
    {
        largest = left;
    }
    if(right < N && arr[largest] < arr[right])
    {
        largest = right;
    }
    if(largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, N, largest);
    }

    return;
}

//USING THIS HEAPIFY, WHICH IS HEAPIFYDOWN WHEN KEY OF PARENT > KEY OF CHILD -> SWITCH WILL LEAD TO SORTING IN DESCENDING ORDER
// void heapify(int *arr, int N, int i)
// {
//     int smallest = i;
//     int left = 2*i+1;
//     int right = 2*i+2;
//     if(left < N && arr[smallest] > arr[left])
//     {
//         smallest = left;
//     }
//     if(right < N && arr[smallest] > arr[right])
//     {
//         smallest = right;
//     }
//     if(smallest != i)
//     {
//         swap(arr[i], arr[smallest]);
//         heapify(arr, N, smallest);
//     }

//     return;
// }

void heapSort(int *arr, int N)
{
    //building maxheap from array
    for(int i = N/2-1; i >= 0; i--)
    {
        heapify(arr, N, i);
    }

    for(int i = N-1; i>0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr,i,0);
    }

    return;
}

// A utility function to print array of size n
void printArray(int *arr, int N)
{
    for (int i = 0; i < N; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int N = sizeof(arr) / sizeof(arr[0]);

    // Function call
    heapSort(arr, N);

    cout << "Sorted array is \n";
    printArray(arr, N);
}