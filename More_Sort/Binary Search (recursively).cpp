/*

Binary sort implementation (recursively)
O(log n)

using: https://www.geeksforgeeks.org/binary-search/

*/

#include <iostream>
using namespace std;

//recursive implementation
int binary_search(int *arr, int low, int high, int x)
{
    if(high >= low)
    {
        int mid = low + (high-low)/2;

        if(arr[mid] == x)
        {
            return mid;
        }
        else if(x > arr[mid])
        {
            return binary_search(arr, mid+1, high, x);
        }
        else if(x < arr[mid])
        {
            return binary_search(arr, low, mid-1, x);
        }
    }

    return -1;

}

// Driver code
int main()
{
    int arr[] = { 2, 3, 4, 10, 40 };
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binary_search(arr, 0, n - 1, x);
    (result == -1)
        ? cout << "Element is not present in array"
        : cout << "Element is present at index " << result;
    return 0;
}