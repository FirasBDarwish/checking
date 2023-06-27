#include <cstddef> //for 'NULL' pointer value, instead of using 'nullptr'
#include <iostream>
using namespace std;

class Node
{
    public:
        int data;
        Node* previous;
        Node* next;
    
    Node()
    {
        this->data = 0;
        this->previous = NULL;
        this->next = NULL;
    }

    Node(int data)
    {
        this->data = data;
        this->previous = NULL;
        this->next = NULL;
    }

};

class DoublyLinkedList
{
    private:
        Node* head;
        Node* tail;
        int length;

    public:
        DoublyLinkedList()
        {
            head = NULL;
            tail = NULL;
            length = 0;
        }

        void insert_front(int data);
        void insert_back(int data);
        void insert_position(int position, int data);
        
        void delete_front();
        void delete_back();
        void delete_position(int position);

        void print();
        void print_backwards();
        
        ~DoublyLinkedList()
        {
            cout << "Deallocating.." << endl;
            Node* current = head;

            while(current != NULL)
            {
                Node* temp = current->next;
                delete current;
                current = temp;

                cout << "Deleted.." << endl;
            }
        }

};

void DoublyLinkedList::delete_position(int position)
{
    if(head == NULL)
    {
        cout << "Cannot delete at position as there are no elements in the list" << endl;
        return;
    }
    else if(position > length || position < 1)
    {
        cout << "Cannot delete at requested position as there exists no element at that position" << endl;
    }
    else if(position == 1)
    {
        this->delete_front();
    }
    else if(position == length)
    {
        this->delete_back();
    }
    else
    {
        Node* current = head;
        for(int i = 1;i<position;i++)
        {
            current=current->next;
        }
        current->next->previous = current->previous;
        current->previous->next = current->next;

        current->next = NULL;
        current->previous = NULL;
        delete current;

        length--;
        cout << "Deleted.." << endl;
    }

    return;
}

void DoublyLinkedList::delete_back()
{
    if(head==NULL)
    {
        cout << "Cannot delete back as there are no elements in the list" << endl;
        return;
    }
    else if(length == 1)
    {
        Node* current = tail;
        head = NULL;
        tail = NULL;
        delete current;
    }
    else
    {
        Node* current = tail;
        current->previous->next = NULL;
        tail = current->previous;

        current->next = NULL;
        current->previous = NULL;
        delete current;
    }

    cout << "Deleted.." << endl;
    length--;
    return;
}

void DoublyLinkedList::delete_front()
{
    if(head == NULL)
    {
        cout << "Cannot delete front as there are no elements in the list" << endl;
        return;
    }
    else if(length == 1)
    {
        Node* current = head;
        head = NULL;
        tail = NULL;
        delete current;
    }
    else
    {
        Node* current = head;
        current->next->previous = NULL;
        head = current->next;
        
        current->next = NULL;
        current->previous = NULL;
        delete current;
    }

    length--;
    cout << "Deleted.." << endl;
    return;
}

void DoublyLinkedList::insert_front(int data)
{
    Node* node = new Node(data);

    if(length == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        head->previous = node;
        node->next = head;
        head = node;
    }

    length++;
    return;
}

void DoublyLinkedList::insert_back(int data)
{
    Node* node = new Node(data);

    if(length == 0)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        node->previous = tail;
        tail = node;
    }
    
    length++;
    return;
}

void DoublyLinkedList::insert_position(int position, int data)
{
    if(head == NULL && position != 1)
    {
        cout << "Insertion at desired position is impossible as there are no elements " << endl;
    }
    else if(head==NULL && position == 1)
    {
        this->insert_front(data);
    }
    else if(position > length || position < 1)
    {
        cout << "Position requested for insertion is not occupied by an element." << endl;
    }
    else
    {
        Node* node = new Node(data);
        Node* current = head;
        for(int i=1;i<position;i++)
        {
            current=current->next;
        }
        cout << "current data: " << current->data << endl;
        node->next = current->next;
        node->previous = current->previous;
        current->next->previous = node;
        current->previous->next = node;
        delete current;
    }
}

void DoublyLinkedList::print()
{
    if(head==NULL)
    {
        cout << "No elements in the doubly linked list. Cannot print forwards." << endl;
    }
    else
    {
        cout << "The DoublyLinked List contains the following elements (printed forwards): " << endl;
        Node* node = head;
        while (node != NULL)
        {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }
       
   return;
}

void DoublyLinkedList::print_backwards()
{
    if(tail == NULL)
    {
        cout << "No elements in the doubly linked list. Cannot print backwards." << endl;
    }
    else
    {
        cout << "The DoublyLinked List contains the following elements (printed backwards): " << endl;
        Node* node = tail;
        while(node != NULL)
        {
            cout << node->data << " ";
            node = node->previous;
        }
        cout << endl;
    }
    return;
}

int main()
{
    DoublyLinkedList a = DoublyLinkedList();
    a.print();
    a.print_backwards();
    a.insert_front(1);
    a.print(); // 1
    a.insert_front(2);
    a.print(); // 2 1
    a.insert_back(3);
    a.print(); // 2 1 3
    a.print_backwards(); // 3 1 2
    
    a.insert_position(2, 7);
    a.print();
    a.print_backwards();

    cout << "------" << endl;

    DoublyLinkedList b = DoublyLinkedList();
    b.insert_position(2,9);
    b.insert_position(1,7);
    b.print();

    cout << "------" << endl;
    DoublyLinkedList c = DoublyLinkedList();
    c.insert_front(2);
    c.insert_back(1);
    c.print();
    c.delete_front();
    c.print();
    c.delete_front();
    c.print_backwards();

    cout << "------" << endl;
    DoublyLinkedList d = DoublyLinkedList();
    d.insert_front(2);
    d.insert_back(1);
    d.print();
    d.delete_back();
    d.print();
    d.delete_back();
    d.print_backwards();

    cout << "------" << endl;
    DoublyLinkedList e = DoublyLinkedList();
    e.insert_front(2);
    e.insert_front(1);
    e.insert_front(0);
    e.print();
    e.delete_position(2);
    e.print();
    e.print_backwards();
    e.insert_back(5);
    e.print();
    e.delete_position(1);
    e.print();
    e.delete_position(3);
    e.delete_position(2);
    e.print_backwards();
    e.print();

}