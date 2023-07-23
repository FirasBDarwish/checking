/*

C++ program for implementation of selection sort

using: https://www.geeksforgeeks.org/selection-sort/

*/

#include <bits/stdc++.h>
using namespace std;

void selection_sort(int *arr, int n)
{
    int i, j, min_index;

    for(i = 0; i < n-1; i++)
    {
        min_index = i;
        for(j= i+1; j<n; j++)
        {
            if(arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if(min_index != i) //for redundancy
            {
                int temp = arr[i];
                arr[i] = arr[min_index];
                arr[min_index] = temp;

                // swap(arr[min_index], arr[i]);
            }
    }
}

// Function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        cout << arr[i] << " ";
        cout << endl;
    }
}
 
// Driver program
int main()
{
    int arr[] = { 64, 25, 12, 22, 11 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    // Function Call
    selection_sort(arr, n);
    cout << "Sorted array: \n";
    printArray(arr, n);
    return 0;
}