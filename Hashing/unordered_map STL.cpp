/*

This uses the unordered_map data structure from C++ STL
    -> this is C++ STL implementation of hash table
    -> different from STL Map:
        ->  STL Map Internal Implementation: It’s implemented
        as a self-balancing red-black tree. Probably the
        two most common self balancing trees are red-black
        tree and AVL trees. 

See 5.6 of 'Data Structures and Algorithm Design in C++' for
more info.

using: https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/

*/


// C++ program to demonstrate 
// functionality of unordered_map
#include <iostream>
#include <unordered_map>
using namespace std;

// int main()
// {
//     unordered_map<string, int> umap;

//     // inserting values by using [] operator
//     umap["GeeksforGeeks"] = 10;
//     umap["Practice"] = 20;
//     umap["Contribute"] = 30;

//     for (auto x: umap)
//     {
//         cout << x.first << ": " << x.second << endl;
//     }

// }

// int main()
// {
//     unordered_map<string, double> umap {  //inserting element directly in map
//     {"One", 1},
//     {"Two", 2},
//     {"Three", 3}
//     };

//         // inserting values by using [] operator
//     umap["PI"] = 3.14;
//     umap["root2"] = 1.414;
//     umap["root3"] = 1.732;
//     umap["log10"] = 2.302;
//     umap["loge"] = 1.0;

//         // inserting value by insert function
//     umap.insert(make_pair("e", 2.718));
    
//     string key = "PI";
//     if (umap.find(key) == umap.end())
//     {
//         cout << key << " not found\n\n";
//     }
//   // If key found then iterator to that 
//   // key is returned
//     else
//     {
//     cout << "Found " << key << "\n\n";
//     }

//     unordered_map<string, double>::iterator itr;
//   cout << "\nAll Elements : \n";
//   for (itr = umap.begin(); 
//        itr != umap.end(); itr++) 
//   {
//     // itr works as a pointer to 
//     // pair<string, double> type 
//     // itr->first stores the key part and
//     // itr->second stores the value part
//     cout << itr->first << "  " << 
//             itr->second << endl;
//   }

//   cout << "---" << endl;

//     //another way to go through all elements
//   for(auto x: umap)
//   {
//     cout << x.first << " : " << x.second << endl;
//   }

// }

// int main()
// {
//     unordered_map<string, int> umap;
//     cout << umap["hello"] << endl; //automatically allocates it as 0

// }

#include <bits/stdc++.h>
  
// Prints frequencies of 
// individual words in str
void printFrequencies(const string &str)
{
    unordered_map<string, int> umap;

    stringstream ss(str);
    string word;
    while(ss >> word)
        umap[word]++;

    unordered_map<string, int>::iterator p;
    for(p=umap.begin();p != end(umap); p++)
    {
        cout << "(" << p->first << "," << p->second << ")" << endl;
    }
}

int main()
{
    string str = "geeks for geeks geeks quiz practice qa for";
    printFrequencies(str);
    return 0; 
}