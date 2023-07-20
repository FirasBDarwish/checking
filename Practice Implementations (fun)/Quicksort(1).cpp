// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

int partition(int *arr, int low, int high)
{
    // int* pivot = &(arr[high]);
    int pivot = arr[high];
    
    int i = low;
    for(int j=low; j<high; j++)
    {
        // if(arr[j] < *pivot)
        if(arr[j] < pivot)
        {
            swap(arr[j], arr[i]);
            i++;
        }
    }
    
    // swap(arr[i], *pivot); pivot is a pointer to address of arr[high], so you're swapping the right addresses
    swap(arr[i], arr[high]);
    
    return i;
}

void quickSort(int *arr, int low, int high)
{
    if (low < high) //if not while
    {
        int mid = partition(arr, low, high);
        quickSort(arr, low, mid-1);
        quickSort(arr, mid+1, high);
    }
}

// Driver Code
int main()
{
    int arr[] = { 10, 7, 8, 9, 1, 5 };
    int N = sizeof(arr) / sizeof(arr[0]);
 
    // Function call
    quickSort(arr, 0, N - 1);
    cout << "Sorted array: " << endl;
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    return 0;
}