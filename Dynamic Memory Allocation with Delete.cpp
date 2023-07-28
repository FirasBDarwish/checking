// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

class One
{
    public:
    int* value;
};

int main()
{
    One* A = new One();
    A->value = new int(4);
    
    One* B = new One();
    B->value = new int(5);
    
    cout << "A value address: " << A->value << endl;
    cout << "A value: " << *(A->value) << endl;
    cout << "B value address: " << B->value << endl;
    cout << "B value: " << *(B->value) << endl;
    
    cout << "A address: " << A << endl;
    cout << "B address: " << B << endl;
    
    *B = *A; //dynamically allocated elements of the class get shallow copied (so now B's value points to A's value which is pointing to new int(4), so they now both point to that same memory address.

    cout << "A value address: " << A->value << endl;
    cout << "A value: " << *(A->value) << endl;
    cout << "B value address: " << B->value << endl;
    cout << "B value: " << *(B->value) << endl;
    
    cout << "A address: " << A << endl;
    cout << "B address: " << B << endl;
    
}

// int main() {
//     // Write C++ code here
//     int* A = new int(3);
//     int* B = new int(4);
//     cout << *B << endl;
    
//     *B = *A; //shallow copy of values in A to B.
    
//     cout << *B << endl;
    
//     delete(A);
    
//     cout << *B << endl;

//     return 0;
// }

// int main()
// {
//     int* A = new int(3);
//     int* B = A;
    
//     delete(B); //deletes the dynamically allocated memory of 3 pointed to by both A and B
    
// }