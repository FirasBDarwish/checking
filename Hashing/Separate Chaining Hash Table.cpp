/*

This is based on section 5.3 of Data Structures and Algorithm Analysis in C++.

We will use rehash() to ensure the hash table's load factor remains around 1.0. 

*/

#include <vector>
#include <list>
#include <functional> // For std::hash

using namespace std;

template <typename HashedObj>
class HashTable
{
    private:
        vector<list<HashedObj>> theLists; //the array of lists
        int currentsize;

        void rehash();
        size_t myhash (const HashedObj & x) const;

    public:
        HashTable(int size = 101);
        bool contains (const HashedObj & x) const;
        
        void makeEmpty();

        bool insert(const HashedObj & x);
        bool insert(HashedObj && x); //accepts r-value
        bool remove(const HashedObj & x);

};

//odd heading here, it has no template
template<>
class hash<string> //so what is this
{
    public:
    size_t operator() (const string & key)
    {
        size_t hashval = 0;

        for(char ch: key)
        {
            hashval = 37*hashval + ch;
        }

        return hashval;
    }

};

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size = 101)
{
    theLists(nextPrime(size));
    /*
    The std::vector constructor is used
    to initialize the array member. It
    creates a std::vector with a size
    equal to the next prime number
    (determined by nextPrime(size)).
    The elements of the vector are
    default-constructed, meaning they
    are initialized to their default values
    based on their type.
    */
    makeEmpty();
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj & x) const
{
    static hash<HashedObj> hf; //uses default hash function for string,
        // can also use a custom 'struct' or 'class' to control how
        // the hash function actually works
        //hf(x) returns large integer that we still need to do modulo on
        //in the textbook's implementation involving hashval = 37*hashval + ch; for every character ch,
            //that also returned large number we need to conduct modulu on.
    return hf(x) % theLists.size();
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for(auto & thisList: theLists)
    {
        thisList.clear();
    }
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj & x) const
{
    auto & whichList = theLists[myhash(x)];
    return ( find(begin(whichList), end(whichList),x) != end(whichList));
    
    /* begin(whichList) is a wrapper for whichList.begin(), both can be used for vectors and lists
    end(whicHList is a wrapper for whichList.end(), both can be used for vectors and lists
    find() takes an iterator to the first position of the sequence, iterator to the final position of the sequence, and the value to be found
    if it does not find it, it returns end(whichList), which is an iterator to the after-final/after-end element of the sequence.
    */

    //see bottom for more explanation on end(list)

}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj & x) //x is its key
{
    auto & whichList = theLists[myhash(x)];
    auto itr = find(begin(whichList), end(whichList), x);

    if(itr == end(whichList))
    {
        return false;
    }

    whichList.erase(itr);
    currentsize--;
    return true;

}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj & x)
{
    auto *whichList = theLists[myhash(x)];

    if(find(begin(whichList), end(whichList), x) != end(whichList))
    {
        return false;
    }
    whichList.push_back(x);

    currentsize++;
    if(currentsize > theLists.size()) //the load factor should stay around 1,
                                    //if currentsize (number of elements) is greater than
                                    //the number of lists (size of vector of lists)
                                    //then there is a load factor > 1, so we need to rehash.
    {
        rehash();
    }

    return true;

}

template <typename HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<list<HashedObj>> oldLists = theLists;

        //create new double-sized, empty table
    theLists.resize(nextPrime(2*theLists.size()));
    for(auto & thisList: theLists)
    {
        thisList.clear();
    }

    currentSize = 0;
    for( auto & thisList: oldLists)
    {
        for(auto & x: thisList)
        {
            insert(std::move(x)); //uses the insert function we developed for rvalue
            /*
            
            Yes, you can remove the use of std::move and pass the elements by lvalue reference in the rehash function. In fact, passing elements by lvalue reference would avoid the need to move elements and would perform the copy operation instead. However, this could lead to additional overhead, especially if HashedObj is expensive to copy.

            When you pass elements by lvalue reference, the insert function will need to create a copy of each element being inserted. This involves invoking the copy constructor of HashedObj, which can be costly if the copy constructor performs deep copying or allocates significant resources.

            On the other hand, using std::move enables the use of move semantics, which allows the elements to be moved and avoids unnecessary copying. If HashedObj has an efficient move constructor, the move operation can be significantly faster than copying, as it transfers the resources (e.g., dynamically allocated memory) from the source object to the destination object without duplication.

            Whether to use std::move or not depends on the characteristics of HashedObj and its associated move constructor. If HashedObj is a simple lightweight type or if its move constructor is not significantly more efficient than its copy constructor, passing by lvalue reference might be reasonable.

            However, if HashedObj is a complex type or its move constructor offers substantial performance gains over copying, using std::move can lead to better performance during rehashing. This is particularly relevant when dealing with large hash tables or when HashedObj contains costly-to-copy resources.

            In summary, you can remove the use of std::move and pass elements by lvalue reference in the rehash function, but be aware that it may result in additional copying overhead. To make an informed decision, consider the characteristics of HashedObj and the potential performance trade-offs between copying and moving elements.

            */
        }
    }
}

//rehash implementation left

/*

// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
using namespace std;

int main() {
    
    vector<int> hello;
    hello.push_back(1);
    hello.push_back(2);
    hello.push_back(3);
    hello.push_back(4);
    
    auto end = hello.end();
    end = end - 2; //end--; to only print 1,2,3
    
    for(auto i=hello.begin();i<end;i++)
    {
        cout << *i << endl;
    }
    
    
}

//this prints: 1,2

*/