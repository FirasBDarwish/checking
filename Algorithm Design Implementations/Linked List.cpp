
#include <cstddef> //for 'NULL' pointer value, instead of using 'nullptr'
#include <iostream>

using namespace std;

class Node
{
    public:
        int data;
        Node* next;

        Node()
        {
            this->data = 0;
            this->next = NULL;
        }

        Node(int data)
        {
            this->data = data;
            this->next = NULL;
        }

        //testing function where you can access a variable or a function for a class/member
        // void Print()
        // {
        //     cout << "HELLO!" << endl;
        // }

};

class LinkedList
{
    private:
        Node* head;
    
    public:
        LinkedList()
        {
            this->head = NULL;
        }

        //insert at the end of the list
        void insert_node(int data);

        //delete based on given position, indexing with head being position 1

        void delete_node(int position);

        //print entire list
        void print_list();
};

//indexing with head being position 1
void LinkedList::delete_node(int position)
{
    if(head == NULL)
    {
        cout << "The Linked List is currently empty and cannot be deleted." << endl;
        return;
    }
    else
    {
        Node* assessor = head; //node used to evaluate length of linked list
        int length = 1;
        while(assessor->next != NULL)
        {
            length++;
            assessor = assessor->next;
        }
        
        Node* current = head; //keeping track of current node
        if(position>length || position < 1)
        {
            cout << "The requested position for deletion is not occupied by an element in the Linked List" << endl;
            return;
        }
        else if(position == 1)
        {
                head = current->next;
                current->next = NULL;
                delete current;
        }
        else
        {
            Node* previous = head;
            for(int i = 1; i<position-1; i++)
            {
                previous = previous->next;
            }
            current = previous->next;
            previous->next = current->next;
            current->next = NULL;
            delete current;

        }
    }
    cout << "Successfully Deleted Element at Position: " << position << endl;
    return; 
}

void LinkedList::insert_node(int data)
{
    Node* node = new Node(data);
   
   if(head == NULL)
    {
        head = node;
        return;
    }
    else
    {
        Node* current = head;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
        return;
    }
}

void LinkedList::print_list()
{
    if (head == NULL)
        {
            cout << "The Linked List is empty and it cannot be printed." << endl;
            return;
        }
    else
        {
        cout << "The Linked List contains the following items: ";
        
        Node* current = head;
        while(current != NULL)
            {
                cout << current->data << "  ";
                //current->Print(); //testing function where you can access a variable or a function for a class/member
                current = current->next;
            }
            cout << endl;
            return;
        }
}

int main()
{
    LinkedList a = LinkedList();
    a.insert_node(3);
    a.print_list();

    a.insert_node(4);
    a.insert_node(1);
    a.print_list();
    a.delete_node(0);
    a.delete_node(1);
    a.print_list();
    a.delete_node(2);
    a.delete_node(2); //length should be 1 here
    a.print_list();
    a.delete_node(1);
    a.print_list();

    a.delete_node(1);
}