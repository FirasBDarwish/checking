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