
/*

This is based on section 4.1 of Algorithm Analysis.

Using: https://www.geeksforgeeks.org/merge-sort/

Time Complexity: O(n log n) for all cases

*/


/*

In C++, the difference between int *arr and int *arr[] as function parameters lies in the type of array being passed.

int *arr: This represents a single-dimensional array of integers. It is typically used when you want to pass an array to a function, and the function only needs to operate on the elements of the array. The pointer arr points to the first element of the array, and you can use pointer arithmetic to access other elements.

Example:

cpp
Copy code
void function(int *arr, int size) {
    // Accessing elements using pointer arithmetic
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}

int main() {
    int myArray[] = {1, 2, 3, 4, 5};
    int size = sizeof(myArray) / sizeof(myArray[0]);
    function(myArray, size);
    return 0;
}
int *arr[]: This represents a two-dimensional array of integers, also known as an array of pointers. Each element of arr is a pointer to an integer array. It is typically used when you want to pass a matrix or a multidimensional array to a function.

Example:

cpp
Copy code
void function(int *arr[], int rows, int cols) {
    // Accessing elements using double indexing
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int row1[] = {1, 2, 3};
    int row2[] = {4, 5, 6};
    int *myMatrix[] = {row1, row2};
    int rows = sizeof(myMatrix) / sizeof(myMatrix[0]);
    int cols = sizeof(row1) / sizeof(row1[0]);
    function(myMatrix, rows, cols);
    return 0;
}
In summary, int *arr represents a single-dimensional array of integers, whereas int *arr[] represents a two-dimensional array (an array of pointers to integer arrays).
*/

#include <iostream>
using namespace std;

//notice the int * arr[] is for two dimensional
void merge(int *arr, int const left, int const mid, int const right)
{

    int subarray_1 = mid - left + 1;
    int subarray_2 = right - mid;

    //we split into two arrays but we fix the order IN THE ORIGINAL LARGER (size N) array.
    int *leftArray = new int[subarray_1];
    int *rightArray = new int[subarray_2];

    for(int i=0; i<subarray_1; i++)
    {
        leftArray[i] = arr[left + i];
    }
    for(int i=0; i<subarray_2;i++)
    {
        rightArray[i] = arr[mid + 1 + i];
    }

    int index_1 = 0, index_2 = 0;
    int index_merged = left;

    while(index_1 < subarray_1 && index_2 < subarray_2)
    {
        if(leftArray[index_1] <= rightArray[index_2])
        {
            arr[index_merged] = leftArray[index_1];
            index_1++;
        }
        else
        {
            arr[index_merged] = rightArray[index_2];
            index_2++;
        }
        index_merged++;
    }

    while(index_1 < subarray_1)
    {
        arr[index_merged] = leftArray[index_1];
        index_1++;
        index_merged++;
    }
    while(index_2 < subarray_2)
    {
        arr[index_merged] = rightArray[index_2];
        index_2++;
        index_merged++;
    }

    delete[] leftArray;
    delete[] rightArray;

    return;
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(int *array, int const begin, int const end)
{
    if(begin >= end)
    {
        return;
    }

    int mid = begin + (end-begin)/2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid+1, end);
    merge(array, begin, mid, end);
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int *A, int size)
{
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}

// Driver code
int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
 
    cout << "Given array is \n";
    printArray(arr, arr_size);
 
    mergeSort(arr, 0, arr_size - 1);
 
    cout << "\nSorted array is \n";
    printArray(arr, arr_size);
    return 0;
}

