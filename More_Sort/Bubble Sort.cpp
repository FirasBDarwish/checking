/*

Optimized implementation of Bubble Sort (O(n^2))

using: https://www.geeksforgeeks.org/bubble-sort/


*/


#include <bits/stdc++.h>
using namespace std;
  
// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
    bool swapped;

    for(int i=0; i<n-1; i++)
    {
        swapped=false;
        for(int j=0; j<n-i-1; j++) //-i as we are pushing the largest element to the right
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(swapped == false)
        {
            break;
        }

    }

}

// Function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}
  
// Driver program to test above functions
int main()
{
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int N = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, N);
    cout << "Sorted array: \n";
    printArray(arr, N);
    return 0;
}