/*

Implementing fibnonnaci sequence using recursion, as opposed to with
dynamic programming (see Algoroithm Design Implementations/Dynamic Programming/Fibonnaci Sequence)

*/

#include <iostream>

using namespace std;

int Fibonacci(int n)
{
    if(n == 0)
    {
        return 0;
    }
    if(n==1)
    {
        return 1;
    }

    return Fibonacci(n-1) + Fibonacci(n-2);
}

int main()
{
    int n = 6;
    cout << "Fibonacci of " << n << " is " << Fibonacci(n) << endl;
}