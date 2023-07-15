#ifndef HASH
#define HASH

#include "BinaryTree.hpp"

#include <fstream>

class Hash{
  public:

    Hash();
    Hash(int size);
    ~Hash();

    void Insert(int Dest,
                int ID,
                std::string &message,
                int words,
                std::ofstream &FileOut);
    void Search(int InBox,
                int ID,
                std::ofstream &FileOut);
    void Erase(int InBox,
                int ID,
                std::ofstream &FileOut);
    void AccessHash();

    BinaryTree* HashTable;
    int Size;
};

#endif