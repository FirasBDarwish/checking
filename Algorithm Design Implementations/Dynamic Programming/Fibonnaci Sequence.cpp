/*

This is a different approach from using recursion.

See: https://www.tutorialspoint.com/cplusplus-program-to-find-fibonacci-numbers-using-dynamic-programming

*/

#include<iostream>
using namespace std;

int genFibonacci(int n)
{
    int fibo[n+2];
    fibo[0] = 0;
    fibo[1] = 1;
    for(int i=2; i<=n; i++)
    {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }
    return fibo[n];
}

int main()
{
    int n = 3;
    cout << "Fibo of " << n << " is " << genFibonacci(n) << endl;

    return 0;

}