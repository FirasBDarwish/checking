#include <iostream>
using namespace std;

template <class T>
class queue
{
    private:
    int top; //index used to add new elements (elements added most recently/removed last are closer to this index)
    int bottom; //index used with removal elements (elements added first/removed first are closer to this index)
    int size; //size used for initialization
    T* arr;

    public:
    queue(int size);
    ~queue();

    void enqueue(T& a);
    void dequeue();
    void print();

};

template <class T>
queue<T>::queue(int size)
    {
        this->size=size;
        arr = new T[this->size];
        top = bottom = 0;
    }

template <class T>
queue<T>::~queue()
    {
        delete[] arr;
    }

template <class T>
void queue<T>::enqueue(T& a)
    {
        if(top == size)
        {
            cout << "Queue is full" << endl;
            return;
        }
        else
        {
            arr[top++] = a;
        }
    }

template<class T>
void queue<T>::dequeue()
    {
        if(top == bottom)
        {
            cout << "Queue is empty" << endl;
            return;
        }
        else
        {
            for(int i = 0; i<top-1;i++)
            {
                arr[i] = arr[i+1];
            }
            top--;
        }
    }

template<class T>
void queue<T>::print()
    {
        for(int i=0;i<top;i++)
        {
            cout << "Element " << i << ": " << arr[i] << endl;
        }
    }

int main()
{
    queue<int> test_queue(10); //do not forget template argument
    int six = 6, five = 5;
    test_queue.enqueue(six);
    test_queue.enqueue(five);
    test_queue.dequeue();
    test_queue.print();
}

