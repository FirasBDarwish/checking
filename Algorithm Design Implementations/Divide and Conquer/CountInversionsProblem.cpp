/*

This is an algorithm to count the number of inversions in an array. This is based on section 4.3 of Algorithm Design. Pseudocode offered there.

Using (my brains!).

If you want a different way to do this, see: https://www.geeksforgeeks.org/cpp-program-for-counting-inversions-in-an-array-set-1-using-merge-sort/

*/

#include <iostream>
using namespace std;

// struct to_return
// {
//     int r;
//     int* arr;

// };

// to_return Merge_and_Count()
int Merge_and_Count(int *arr, int start1, int end1, int start2, int end2)
{
    int index1 = start1;
    int index2 = start2;
    int Count = 0;

    int* temp = new int[end2 - start1 + 1];
    int indexmain = 0;

    while(index1 <= end1 && index2 <= end2)
    {
       if(arr[index2] < arr[index1])
       {
        temp[indexmain] = arr[index2];
        Count = Count + (end1-index1+1);
        index2++;
       }
       else
       {
        temp[indexmain] = arr[index1];
        index1++;
       }

        indexmain++;
    }

    while(index1 <= end1)
    {
        temp[indexmain] = arr[index1];
        indexmain++;
        index1++;
    }

    while(index2 <= end2)
    {
        temp[indexmain] = arr[index2];
        indexmain++;
        index2++;
    }

    int index_og = start1;
    for(int i=0; i<(end2-start1+1); i++)
    {
        arr[index_og] = temp[i];
        index_og++;
    }

    return Count;
}

// to_return Sort_and_Count(int *arr, int start, int end)
int Sort_and_Count(int *arr, int start, int end)
{
    int inversions=0;
    if (start==end)
    {
    }
    else
    {
        int mid = start+(end-start)/2;
        // to_return A = Sort_and_Count(arr, start, mid);
        // to_return B = Sort_and_Count(arr, mid+1, end);
        // to_return C = Merge_and_Count(A, B);
        int A = Sort_and_Count(arr, start, mid);
        int B = Sort_and_Count(arr, mid+1, end);
        int C = Merge_and_Count(arr, start, mid, mid+1, end);

        // inversions = A.r + B.r + C.r;
        inversions = A + B + C;
    }

    return inversions;

}

int main()
{
    int array[5] = {1,20,6,4,5};

    for(int i = 0; i< 5; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

    int inversions = Sort_and_Count(array, 0, 4);
    cout << "The number of inversions detected in this array is " << inversions << "." << endl;

    for(int i = 0; i< 5; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;

}