/*

This is a largely erroneous implementation of quadratic probing from the "Data Structures and Algorithm Design in C++" book.

It is also missing the rehash function.

*/


/*

In the provided HashEntry struct, there are two constructors:

Constructor taking const HashedObj& e:
This constructor is used when you want to create a HashEntry object by passing a const lvalue reference to a HashedObj. It allows you to create a HashEntry instance with a constant reference to an existing HashedObj object. The const qualifier ensures that the HashedObj passed to this constructor cannot be modified within the constructor.

For example, you can use this constructor to create a HashEntry object like this:

HashedObj obj = someValue;
HashEntry entry(obj, EntryType::SOME_INFO);
Here, entry is created with a copy of obj, and the HashedObj member element inside entry is initialized with the value of obj.

Constructor taking HashedObj&& e (rvalue reference):
This constructor is used when you want to create a HashEntry object by passing an rvalue reference to a HashedObj. An rvalue reference (&&) is used to bind to temporary objects or objects that can be moved. It allows you to create a HashEntry instance while potentially transferring ownership or resources from the HashedObj being passed.

For example, you can use this constructor to create a HashEntry object like this:


HashEntry entry(HashedObj(someValue), EntryType::SOME_INFO);
In this case, HashedObj(someValue) creates a temporary HashedObj object, and it can be moved into the HashEntry constructor. This avoids an unnecessary copy and may be more efficient, especially if HashedObj is a heavy object or contains expensive-to-copy resources.

In summary, the difference between the two constructors lies in how they accept the HashedObj argument:

The first constructor takes a const lvalue reference (const HashedObj&), suitable for handling lvalues (named objects) and ensuring they won't be modified.
The second constructor takes an rvalue reference (HashedObj&&), suitable for efficiently handling temporary objects and potentially transferring ownership or resources to the HashEntry object being constructed.


I THEN ASKED: why is std::move used?

In the second constructor of the HashEntry struct, std::move is used to cast the HashedObj&& e parameter from an rvalue reference to an xvalue. The purpose of using std::move in this context is to enable efficient move semantics and potentially transfer ownership or resources from the HashedObj being passed to the HashEntry constructor.

Let's dive deeper into what happens when std::move is used:

Rvalue References and Move Semantics:
An rvalue reference (HashedObj&&) can bind to an rvalue (e.g., a temporary object or an object that is about to be destroyed). Rvalue references are used to enable move semantics, which is a mechanism in C++ that allows objects to transfer their resources (e.g., dynamically allocated memory, file handles) efficiently from one object to another without performing expensive deep copies.

std::move Function:
The std::move function is a utility provided by the C++ Standard Library in the <utility> header. It takes an rvalue reference as its argument and returns an xvalue (an "eXpiring value") of that rvalue reference type. It doesn't actually move anything; it's just a cast that transforms an lvalue into an rvalue.

Move Constructor:
In the second constructor, std::move(e) is used to convert the rvalue reference e into an xvalue, and this xvalue is then used to initialize the element member of HashEntry via move construction. If the type HashedObj has an appropriate move constructor, this move constructor will be used to transfer the resources of the passed HashedObj into the element member. The move constructor can efficiently "steal" the resources from the temporary object created in the constructor call, rather than making a costly deep copy.

*/

template <typename HashedObj>
class HashTable
{
    public:
        explicit HashTable(int size = 101);
        bool contains(const HashedObj & x) const;

        void makeEmpty();
        bool insert(const HashedObj & x);
        bool insert(HashedObj && x);
        bool remove(const HashedObj & x);

        enum EntryType { ACTIVE, EMPTY, DELETED };

    private:
        struct HashEntry
        {
            HashedObj element;
            EntryType info;

            HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY): element{ e }, info { i } { } //empty constructor's body {} means there are no additional statements to be executed
            HashEntry( HashedObj && e, EntryType i = EMPTY ): element{ std::move(e) }, info{ i } { } //setting element to (move) e and info to i (both have default values)
        };

        vector<HashEntry> array;
        int currentSize;

        bool isActive(int currentPost) const;
        int findPos( const HashedObj & x) const;
        void rehash();
        size_t myhash( const HashedObj & x) const;
};

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size = 101): array(nextPrime(size))
/*
The std::vector constructor is used to initialize the array member. It creates
a std::vector with a size equal to the next prime number (determined by nextPrime(size)).
The elements of the vector are default-constructed, meaning they are initialized
to their default values based on their type.
*/
{
    makeEmpty();
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    currentSize = 0;
    for(auto & HashEntry: array)
    {
        HashEntry.info = EMPTY;
    }
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj & x) const
{
    return isActive(findPos(x));
}

/*
No, this is just a stupid implementation. There is no mechanism to break out
of the while loop if the element x is not a .element of any index of array.
This is ridiculous as this function is used in the insert function to check
if the element is already in the hashtable. Seeing as this will loop indefinitely
when an element x is not in the hashtable, using findPos in insert will also break the insert
function...

*/
template<typename HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj & x) const //assumes the element X is in the array
{
    int offset = 1;
    int currentPos = myhash(x);

while(array[currentPos].info != EMPTY && array[currentPos].element != x) //empty means it contains an element.. active means it CAN hold an element
{
    currentPos += offset;
    offset += 2; //linear probing..? no it says quadratic in book
    if(currentPos >= array.size())
    {
        currentPost-=array.size(); //n+1 becomes n+1-n = 1
    }
}

    return currentPos;
}

template<typename HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template<typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj & x)
{
    int currentPos = findPos(x);
    if(isActive(currentPos)) //..currentPos only stops while loop when that position is empty.. this will always be false
    {
        return false; //occupied if that position is active
    }

    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    currentSize++;
    if(currentSize > array.size() / 2)
    {
        rehash();
    }

    return true;

}

template<typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj & x)
{
    int currentPos = findPos(x);
    if(!isActive(currentPos))
    {
        return false;
    }

    array[currentPos].info = DELETED;
    return true;
}