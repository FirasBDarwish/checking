/*

Unordered set of case-insensitive strings can be maintained.

*/

#include <bits/stdc++.h>
using namespace std;

int main()
{

unordered_set<string> stringSet;

stringSet.insert("code");
stringSet.insert("in");
stringSet.insert("C++");
stringSet.insert("is");
stringSet.insert("fast");

string key = "slow";

// find returns end iterator if key is not found,
    // else it returns iterator to that key
if(stringSet.find(key) == stringSet.end())
{
    cout << key << " not found." << endl; 
}
else
{
    cout << key << " found!" << endl;
}

key = "C++";
if(stringSet.find(key) == stringSet.end())
{
    cout << key << " not found." << endl; 
}
else
{
    cout << key << " found!" << endl;
}

cout << endl << "All elements : " << endl;
    unordered_set<string>::iterator itr; //can do auto itr
    for (itr = stringSet.begin(); itr != stringSet.end();
         itr++)
        cout << (*itr) << endl;

};

/*

ADding custom hash function as well as custom comparison operator:

What is this code doing in C++?

class CaseInsensitiveStringHash
2 {
3 public:
4 size_t operator( ) ( const string & s ) const
5 {
6 static hash<string> hf;
7 return hf( toLower( s ) ); // toLower implemented elsewhere
8 }
9
10 bool operator( ) ( const string & lhs, const string & rhs ) const
11 {
12 return equalsIgnoreCase( lhs, rhs ); // equalsIgnoreCase is elsewhere
13 }
14 };
15
16 unordered_set<string,CaseInsensitiveStringHash,CaseInsensitiveStringHash> s;

ChatGPT
This C++ code defines a custom hash function and a custom equality comparison function for strings with case-insensitive behavior. It then uses these custom functions to create an unordered_set of strings, where the hash function and equality comparison are case-insensitive.

Let's break down the code:

The code begins by defining a class called CaseInsensitiveStringHash, which will serve as the functor for hashing and equality comparison.

In lines 4-8, the class defines the operator() for hashing a string (size_t operator()(const string &s) const). The function uses the standard library hash function from <functional> to compute the hash value of a given string. However, before hashing, it converts the input string s to lowercase using a function called toLower (implemented elsewhere). This ensures that the hash function treats strings with the same characters but different cases as equivalent.

In lines 10-13, the class defines the operator() for comparing two strings (bool operator()(const string &lhs, const string &rhs) const). The function uses a custom function called equalsIgnoreCase (implemented elsewhere) to compare the two strings case-insensitively. This function returns true if the two strings are equal, regardless of their letter case.

Finally, in line 16, the code creates an unordered_set of strings named s. This set uses the CaseInsensitiveStringHash both as the hash function and the equality comparison function. As a result, all strings stored in this unordered_set will be case-insensitive when it comes to hashing and equality comparisons.

In summary, the CaseInsensitiveStringHash class provides custom hashing and equality comparison for strings, making sure that strings with different cases but the same characters are considered equal. It is then used as a template argument when creating the unordered_set of strings, ensuring that the set stores and operates on strings in a case-insensitive manner.

*/