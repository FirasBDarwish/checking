#include <iostream>
using namespace std;

template <class T>
class stack
{
    private:
    T* arr;
    int size; //size of stack
    int top; //where the top of our stack is, can help with keeping track of capacity

    public:
    stack(int size);
    ~stack();

    void push(T &a);
    T peek();
    void pop();
    int get_size();
    //can add is_full and is_empty as well (and reuse them in some of my other functions)

    void print(); //added by me to view elements in stack
};

template <class T>
stack<T>::stack(int size)
{
    this->size = size;
    arr = new T[this->size];
    top = -1;
}

template <class T>
stack<T>::~stack()
{
    delete[] arr;
}

template <class T>
void stack<T>::push(T &a)
{
    if (top==size-1)
    {
        cout << "Error. Capacity reached." << endl;
        return;
    }
    arr[++top] = a;
}

template <class T>
T stack<T>::peek()
{
    if(top == -1)
    {
        cout << "No elements present in stack." << endl;
    }
    else
    {
    return arr[top];
    }
}

template <class T>
void stack<T>::pop()
{
    if(top == -1)
    {
        cout << "No elements present in stack." << endl;
    }
    else
    {
        top--; //return arr[top--]; is optional if you want to return element being popped
    }
}

template <class T>
int stack<T>::get_size()
{
    return top+1;
}

template <class T>
void stack<T>::print()
{
    for(int i = 0; i< this->get_size();i++) //can just do i<size()
    {
        cout << "Element " << i << ": " << arr[i] << endl;
    }
}

int main()
{
    stack<int> test(10);
    //if passing by reference to push(): must make sure integers being used with push are named variables
    int four = 4;
    test.push(four); //test.push(4);
    int five = 5;
    test.push(five); //test.push(5);
    test.pop();
    test.print();
}
