#include <iostream>

using namespace std;

int main()
{
    int* A = new int(30);
    int* B = A;
    int* C = B;

    //so now C and B point to the memory address pointed to by A (which is where the 30 is stored)
    
    cout << C << " " << B << endl;
    
    B = new int(20);

    //B now points to a new memory address (where the 20 is stored)
    
    cout << *C << endl;
    cout << C << " " << B << endl;
    
    //C still points to memory address A (where the 30 is stored)

    return 0;
}
