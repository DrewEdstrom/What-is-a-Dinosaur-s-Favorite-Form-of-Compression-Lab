#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <fstream>

//represents a node in a huffman tree
struct Node 
{
    char c;    //the character represented by the node
    int freq;   //the frequency of the character in the string
    Node *left, *right;     //the left and right child nodes
    
    Node(char ch, int f) 
    : 
    c(ch),
    freq(f),
    left(nullptr),
    right(nullptr)
    {
    }
};

//used to compare entries in the priority queue
struct Compare 
{
    bool operator()(Node* a, Node* b) 
    {
        return a->freq > b->freq;
    }
};

//creates huffman codes
void create_codes(Node* root, std::unordered_map<char, std::string> &codes, std::string code);

//builds a huffman tree as well as returns the compressed string
std::pair<std::unordered_map<char, std::string>, std::string> compress(std::string uncompressed_txt);

//returns the decompressed string
std::string decompress(std::string compressed_txt, std::unordered_map<char, std::string> codes);
