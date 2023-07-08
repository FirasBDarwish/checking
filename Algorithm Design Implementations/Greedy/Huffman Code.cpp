/*

This is from section 5.8 of Algorithm Design.

Some more information on the bool operator(): https://en.cppreference.com/w/cpp/container/priority_queue
    -> and why it needs to be inverted, priority_queue is by default max_heap so you need to flip the comparison operator's logic
    as the 'final element' in the ordering is the first element to be taken out, so your comparison operator should make it such 
    that the final element in the ordering is the one with the minimum key to be extracted first.

*/

// C++(STL) program for Huffman Coding with STL
#include <bits/stdc++.h>
using namespace std;

struct MinHeapNode
{
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {
        this->data = data;
        this->freq = freq;
        left = NULL;
        right = NULL;
    }

};

struct compare
{
    //could also be pass by referenec MinHeapNode &l, MinHeapNode &r
        //but you have to change line 36 to l.freq and r.freq (as you are not passing pointed but by
            //reference to the actual variable, MinHeapNode instantiation)
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

void printCodes(MinHeapNode* root, string str)
{
    if(!root)
    {
        return;
    }

    //allows us to skip INTERNAL nodes
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
};

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree

            //could be char data[], int freq[]
void HuffmanCodes(char *data, int *freq, int size) //if size was not given can find length using sizeof..?
{
    MinHeapNode* left, *right, *top;

                //do you need the * in MinHeapNode*? sure, otherwise you'd be having values, just make them match
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for(int i=0; i<size ;i++)
    {
        minHeap.push(new MinHeapNode(data[i], freq[i]));
    }

    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top-> right = right;

        minHeap.push(top); //we need to include it in case the sum of frequencies
                        //summed with another frequency is the least sum

    }

    printCodes(minHeap.top(), "");

}

// Driver Code
int main()
{
 
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
 
    int size = sizeof(arr) / sizeof(arr[0]);
 
    HuffmanCodes(arr, freq, size);
 
    return 0;
}

