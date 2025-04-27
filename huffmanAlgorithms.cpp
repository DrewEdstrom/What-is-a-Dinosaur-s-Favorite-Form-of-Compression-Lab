#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <fstream>
#include "huffmanAlgorithms.h"

using namespace std;

//creates huffman codes
void create_codes(Node* root, unordered_map<char, string> &codes, string code = "") 
{
    if (!root)
    {
        return;
    }
    if (root->c != '\0')
    {
        codes[root->c] = code;
    }

    create_codes(root->left, codes, code + "0");
    create_codes(root->right, codes, code + "1");
}

//builds a huffman tree and returns the compressed string
pair<unordered_map<char, string>, string> compress(string uncompressed_txt) 
{
    unordered_map<char, int> freq;

    //count the frequency of each character in the string provided
    for (char c : uncompressed_txt)
    {
        freq[c]++;
    }
    
    //a priority queue will act as our huffman tree
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    //add each key-value pair from freq to the priority queue
    for (auto &pair : freq)
    {
        pq.push(new Node(pair.first, pair.second));
    }

    //merge each tree until we have a single one
    while (pq.size() > 1) 
    {
        Node *left = pq.top(); 
        pq.pop();

        Node *right = pq.top(); 
        pq.pop();

        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    
    //root node of the huffman tree is the top of the priority queue
    Node* root = pq.top();
    unordered_map<char, string> codes;

    create_codes(root, codes);
    
    string compressed_txt;

    for (char c : uncompressed_txt)
    {
        compressed_txt += codes[c];
    }

    return {codes, compressed_txt};
}

//returns the decompressed string
string decompress(string compressed_txt, unordered_map<char, string> codes) 
{
    unordered_map<string, char> reverseCodes;
    
    for (auto &pair : codes)
    {
        reverseCodes[pair.second] = pair.first;
    }

    string decompressed_txt, buff;

    for (char c : compressed_txt) 
    {
        buff += c;

        if (reverseCodes.count(buff)) 
        {
            decompressed_txt += reverseCodes[buff];
            buff.clear();
        }
    }

    return decompressed_txt;
}
