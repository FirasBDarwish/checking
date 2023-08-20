/*

use: https://www.programiz.com/dsa/priority-queue#:~:text=Priority%20queue%20can%20be%20implemented,efficient%20implementation%20of%20priority%20queues.

Priority queue using binary heap: https://www.geeksforgeeks.org/priority-queue-using-binary-heap/
This second link is very similar to binary heap as binary heap as a structure works well with the motivation behind priority queues.

*important: minheap using priority_queue stl: https://www.geeksforgeeks.org/implement-min-heap-using-stl/
*/


#include <iostream>
using namespace std;

// C++ program to demonstrate the use of priority_queue
#include <iostream>
#include <queue>
using namespace std;
 
 /* Using STL library (implemented as maxheap by default, multiply all inputted values by -1 to change to minheap)
 
 // driver code
int main()
{
    int arr[6] = { 10, 2, 4, 8, 6, 9 };
 
    // defining priority queue
    priority_queue<int> pq;
 
    // printing array
    cout << "Array: ";
    for (auto i : arr) {
        cout << i << ' ';
    }
    cout << endl;
    // pushing array sequentially one by one
    for (int i = 0; i < 6; i++) {
        pq.push(arr[i]);
    }
 
    // printing priority queue (MAX HEAP)
    cout << "Priority Queue: ";
    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
 
    return 0;
}

 */
