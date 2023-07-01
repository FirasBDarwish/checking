
/*
Using: https://www.geeksforgeeks.org/cpp-program-for-quicksort/

helpful videos: https://www.youtube.com/watch?v=SLauY6PpjW4&ab_channel=HackerRank
another helpful 4-minute video: https://www.youtube.com/watch?v=Hoixgm4-P4M&ab_channel=MichaelSambol
THE great explanatory video: https://www.youtube.com/watch?v=7h1s2SojIRw&ab_channel=AbdulBari

*/

#include <iostream>
using namespace std;


int partition(int *arr, int low, int high)
{


    int index = 0, pivot = arr[high], pivotIndex;
    int* temp = new int[high-low+1];


    for(int i=low; i<= high; i++)
    {
      if(arr[i] < pivot)
      {
        temp[index] = arr[i];
        index++;
      }

    }

    temp[index] = pivot;
    index++;

    for (int i = low; i < high; i++) // pushing all the elements in temp which are greater than pivotElement
    {
        if(arr[i] > pivot)
        {
            temp[index] = arr[i];
            index++;
        }
    }

    index=0;
    for(int i=low; i<=high; i++)
    {
      if(arr[i] == pivot)
      {
        pivotIndex = i;
      }
      arr[i] = temp[index];
      index++;
    }

  delete[] temp;

  return pivotIndex;
}

void quickSort(int *arr, int low, int high)
{
    if(low<high)
    {
        int partition_index = partition(arr, low, high);
        quickSort(arr, low, partition_index-1);
        quickSort(arr, partition_index+1, high);
    }
    return;
}

int main()
{   
    const int size = 9;
    int arr[size] = {5, 12, 7, 1, 13, 2 ,23, 11, 18};
       
      cout << "Unsorted array : ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    printf("\n");
 
    quickSort(arr, 0, size - 1);
     
      cout << "Sorted array : ";
    for (int i = 0; i < size; i++)
    {
       cout << arr[i] << " ";
    }
    cout << endl;
   
      return 0;
}

