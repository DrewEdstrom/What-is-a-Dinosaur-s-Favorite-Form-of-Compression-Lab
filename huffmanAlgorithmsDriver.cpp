#include <iostream>
#include <string>
#include "huffmanAlgorithms.h"

using namespace std;

int main()
{
    string text = "Hello World";
    auto [codes, comp_txt] = compress(text);

    cout << "Compression Table:\n";
    for (auto &pair : codes)
        cout << pair.first << " : " << pair.second << "\n";
    
    cout << "Compressed String: " << comp_txt << "\n";

    string decomp_txt = decompress(comp_txt, codes);
    cout << "Decompressed String: " << decomp_txt << "\n";

    return 0;
}
